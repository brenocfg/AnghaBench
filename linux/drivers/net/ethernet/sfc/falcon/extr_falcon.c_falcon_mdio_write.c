#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct falcon_nic_data {int /*<<< orphan*/  mdio_lock; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AB_MD_DEV_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_GC ; 
 int /*<<< orphan*/  FRF_AB_MD_PHY_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_PRT_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_TXD ; 
 int /*<<< orphan*/  FRF_AB_MD_WRC ; 
 int /*<<< orphan*/  FR_AB_MD_CS ; 
 int /*<<< orphan*/  FR_AB_MD_ID ; 
 int /*<<< orphan*/  FR_AB_MD_PHY_ADR ; 
 int /*<<< orphan*/  FR_AB_MD_TXD ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int falcon_gmii_wait (struct ef4_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_vdbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int falcon_mdio_write(struct net_device *net_dev,
			     int prtad, int devad, u16 addr, u16 value)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	struct falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;
	int rc;

	netif_vdbg(efx, hw, efx->net_dev,
		   "writing MDIO %d register %d.%d with 0x%04x\n",
		    prtad, devad, addr, value);

	mutex_lock(&nic_data->mdio_lock);

	/* Check MDIO not currently being accessed */
	rc = falcon_gmii_wait(efx);
	if (rc)
		goto out;

	/* Write the address/ID register */
	EF4_POPULATE_OWORD_1(reg, FRF_AB_MD_PHY_ADR, addr);
	ef4_writeo(efx, &reg, FR_AB_MD_PHY_ADR);

	EF4_POPULATE_OWORD_2(reg, FRF_AB_MD_PRT_ADR, prtad,
			     FRF_AB_MD_DEV_ADR, devad);
	ef4_writeo(efx, &reg, FR_AB_MD_ID);

	/* Write data */
	EF4_POPULATE_OWORD_1(reg, FRF_AB_MD_TXD, value);
	ef4_writeo(efx, &reg, FR_AB_MD_TXD);

	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_MD_WRC, 1,
			     FRF_AB_MD_GC, 0);
	ef4_writeo(efx, &reg, FR_AB_MD_CS);

	/* Wait for data to be written */
	rc = falcon_gmii_wait(efx);
	if (rc) {
		/* Abort the write operation */
		EF4_POPULATE_OWORD_2(reg,
				     FRF_AB_MD_WRC, 0,
				     FRF_AB_MD_GC, 1);
		ef4_writeo(efx, &reg, FR_AB_MD_CS);
		udelay(10);
	}

out:
	mutex_unlock(&nic_data->mdio_lock);
	return rc;
}