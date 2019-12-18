#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;
struct emac_adapter {struct net_device* netdev; int /*<<< orphan*/  phydev; TYPE_1__ irq; scalar_t__ base; TYPE_2__ rx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIS_INT ; 
 scalar_t__ EMAC_INT_MASK ; 
 scalar_t__ EMAC_INT_STATUS ; 
 int /*<<< orphan*/  emac_mac_reset (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_rx_q_free_descs (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_tx_q_descs_free (struct emac_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_reset_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void emac_mac_down(struct emac_adapter *adpt)
{
	struct net_device *netdev = adpt->netdev;

	netif_stop_queue(netdev);
	napi_disable(&adpt->rx_q.napi);

	phy_stop(adpt->phydev);

	/* Interrupts must be disabled before the PHY is disconnected, to
	 * avoid a race condition where adjust_link is null when we get
	 * an interrupt.
	 */
	writel(DIS_INT, adpt->base + EMAC_INT_STATUS);
	writel(0, adpt->base + EMAC_INT_MASK);
	synchronize_irq(adpt->irq.irq);

	phy_disconnect(adpt->phydev);

	emac_mac_reset(adpt);

	emac_tx_q_descs_free(adpt);
	netdev_reset_queue(adpt->netdev);
	emac_rx_q_free_descs(adpt);
}