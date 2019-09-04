#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xgene_enet_pdata {int rxq_cnt; int cq_cnt; TYPE_1__** tx_ring; struct xgene_enet_desc_ring** rx_ring; } ;
struct xgene_enet_desc_ring {int /*<<< orphan*/  irq_name; int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct xgene_enet_desc_ring* cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* ndev_to_dev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xgene_enet_rx_irq ; 
 int /*<<< orphan*/  xgene_enet_set_irq_name (struct net_device*) ; 

__attribute__((used)) static int xgene_enet_register_irq(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct device *dev = ndev_to_dev(ndev);
	struct xgene_enet_desc_ring *ring;
	int ret = 0, i;

	xgene_enet_set_irq_name(ndev);
	for (i = 0; i < pdata->rxq_cnt; i++) {
		ring = pdata->rx_ring[i];
		irq_set_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(dev, ring->irq, xgene_enet_rx_irq,
				       0, ring->irq_name, ring);
		if (ret) {
			netdev_err(ndev, "Failed to request irq %s\n",
				   ring->irq_name);
		}
	}

	for (i = 0; i < pdata->cq_cnt; i++) {
		ring = pdata->tx_ring[i]->cp_ring;
		irq_set_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(dev, ring->irq, xgene_enet_rx_irq,
				       0, ring->irq_name, ring);
		if (ret) {
			netdev_err(ndev, "Failed to request irq %s\n",
				   ring->irq_name);
		}
	}

	return ret;
}