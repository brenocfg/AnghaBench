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
struct net_device {int dummy; } ;
struct emac_irq {int /*<<< orphan*/  irq; } ;
struct emac_adapter {int /*<<< orphan*/  netdev; struct emac_irq irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_isr ; 
 int emac_mac_rx_tx_rings_alloc_all (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_mac_rx_tx_rings_free_all (struct emac_adapter*) ; 
 int emac_mac_up (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_close (struct emac_adapter*) ; 
 int emac_sgmii_open (struct emac_adapter*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct emac_irq*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct emac_irq*) ; 

__attribute__((used)) static int emac_open(struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);
	struct emac_irq	*irq = &adpt->irq;
	int ret;

	ret = request_irq(irq->irq, emac_isr, 0, "emac-core0", irq);
	if (ret) {
		netdev_err(adpt->netdev, "could not request emac-core0 irq\n");
		return ret;
	}

	/* allocate rx/tx dma buffer & descriptors */
	ret = emac_mac_rx_tx_rings_alloc_all(adpt);
	if (ret) {
		netdev_err(adpt->netdev, "error allocating rx/tx rings\n");
		free_irq(irq->irq, irq);
		return ret;
	}

	ret = emac_sgmii_open(adpt);
	if (ret) {
		emac_mac_rx_tx_rings_free_all(adpt);
		free_irq(irq->irq, irq);
		return ret;
	}

	ret = emac_mac_up(adpt);
	if (ret) {
		emac_mac_rx_tx_rings_free_all(adpt);
		free_irq(irq->irq, irq);
		emac_sgmii_close(adpt);
		return ret;
	}

	return 0;
}