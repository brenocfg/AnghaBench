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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdio_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  DATA ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  MAC_MDIOSCAR ; 
 int /*<<< orphan*/  MAC_MDIOSCCDR ; 
 int XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int xgbe_create_mdio_sca (int,int) ; 

__attribute__((used)) static int xgbe_read_ext_mii_regs(struct xgbe_prv_data *pdata, int addr,
				  int reg)
{
	unsigned int mdio_sca, mdio_sccd;

	reinit_completion(&pdata->mdio_complete);

	mdio_sca = xgbe_create_mdio_sca(addr, reg);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCAR, mdio_sca);

	mdio_sccd = 0;
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, CMD, 3);
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, BUSY, 1);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCCDR, mdio_sccd);

	if (!wait_for_completion_timeout(&pdata->mdio_complete, HZ)) {
		netdev_err(pdata->netdev, "mdio read operation timed out\n");
		return -ETIMEDOUT;
	}

	return XGMAC_IOREAD_BITS(pdata, MAC_MDIOSCCDR, DATA);
}