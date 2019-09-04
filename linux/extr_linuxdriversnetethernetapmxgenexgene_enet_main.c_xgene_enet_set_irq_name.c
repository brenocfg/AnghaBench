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
struct xgene_enet_desc_ring {int /*<<< orphan*/  irq_name; } ;
struct net_device {char* name; } ;
struct TYPE_2__ {struct xgene_enet_desc_ring* cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_ID_SIZE ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void xgene_enet_set_irq_name(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct xgene_enet_desc_ring *ring;
	int i;

	for (i = 0; i < pdata->rxq_cnt; i++) {
		ring = pdata->rx_ring[i];
		if (!pdata->cq_cnt) {
			snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-rx-txc",
				 ndev->name);
		} else {
			snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-rx-%d",
				 ndev->name, i);
		}
	}

	for (i = 0; i < pdata->cq_cnt; i++) {
		ring = pdata->tx_ring[i]->cp_ring;
		snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-txc-%d",
			 ndev->name, i);
	}
}