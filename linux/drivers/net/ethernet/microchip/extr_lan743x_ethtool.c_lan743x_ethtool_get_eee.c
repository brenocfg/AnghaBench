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
typedef  int u32 ;
struct phy_device {int /*<<< orphan*/  drv; } ;
struct net_device {struct phy_device* phydev; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; } ;
struct ethtool_eee {int eee_enabled; int eee_active; int advertised; int lp_advertised; int tx_lpi_enabled; int tx_lpi_timer; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_EEE_EN_ ; 
 int /*<<< orphan*/  MAC_EEE_TX_LPI_REQ_DLY_CNT ; 
 int /*<<< orphan*/  drv ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int phy_ethtool_get_eee (struct phy_device*,struct ethtool_eee*) ; 

__attribute__((used)) static int lan743x_ethtool_get_eee(struct net_device *netdev,
				   struct ethtool_eee *eee)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;
	u32 buf;
	int ret;

	if (!phydev)
		return -EIO;
	if (!phydev->drv) {
		netif_err(adapter, drv, adapter->netdev,
			  "Missing PHY Driver\n");
		return -EIO;
	}

	ret = phy_ethtool_get_eee(phydev, eee);
	if (ret < 0)
		return ret;

	buf = lan743x_csr_read(adapter, MAC_CR);
	if (buf & MAC_CR_EEE_EN_) {
		eee->eee_enabled = true;
		eee->eee_active = !!(eee->advertised & eee->lp_advertised);
		eee->tx_lpi_enabled = true;
		/* EEE_TX_LPI_REQ_DLY & tx_lpi_timer are same uSec unit */
		buf = lan743x_csr_read(adapter, MAC_EEE_TX_LPI_REQ_DLY_CNT);
		eee->tx_lpi_timer = buf;
	} else {
		eee->eee_enabled = false;
		eee->eee_active = false;
		eee->tx_lpi_enabled = false;
		eee->tx_lpi_timer = 0;
	}

	return 0;
}