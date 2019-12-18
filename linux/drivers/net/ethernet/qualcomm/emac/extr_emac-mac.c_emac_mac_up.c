#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; } ;
struct emac_adapter {TYPE_5__ rx_q; TYPE_2__* phydev; scalar_t__ base; TYPE_1__ irq; struct net_device* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ DIS_INT ; 
 scalar_t__ EMAC_INT_MASK ; 
 scalar_t__ EMAC_INT_STATUS ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int /*<<< orphan*/  emac_adjust_link ; 
 int /*<<< orphan*/  emac_mac_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_rx_descs_refill (struct emac_adapter*,TYPE_5__*) ; 
 int /*<<< orphan*/  emac_mac_rx_tx_ring_reset_all (struct emac_adapter*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_print (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int phy_connect_direct (struct net_device*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int emac_mac_up(struct emac_adapter *adpt)
{
	struct net_device *netdev = adpt->netdev;
	int ret;

	emac_mac_rx_tx_ring_reset_all(adpt);
	emac_mac_config(adpt);
	emac_mac_rx_descs_refill(adpt, &adpt->rx_q);

	adpt->phydev->irq = PHY_POLL;
	ret = phy_connect_direct(netdev, adpt->phydev, emac_adjust_link,
				 PHY_INTERFACE_MODE_SGMII);
	if (ret) {
		netdev_err(adpt->netdev, "could not connect phy\n");
		return ret;
	}

	phy_attached_print(adpt->phydev, NULL);

	/* enable mac irq */
	writel((u32)~DIS_INT, adpt->base + EMAC_INT_STATUS);
	writel(adpt->irq.mask, adpt->base + EMAC_INT_MASK);

	phy_start(adpt->phydev);

	napi_enable(&adpt->rx_q.napi);
	netif_start_queue(netdev);

	return 0;
}