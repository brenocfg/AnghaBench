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
struct TYPE_2__ {int tx_stopped; int /*<<< orphan*/  reclaim_tq; int /*<<< orphan*/  sysctl_bar; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; int /*<<< orphan*/  txqueue_wake; } ;
struct qtnf_bus {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int TOPAZ_IPC_IRQ_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_LH_IPC4_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_RC_TX_STOP_IRQ ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtnf_try_stop_xmit(struct qtnf_bus *bus, struct net_device *ndev)
{
	struct qtnf_pcie_topaz_state *ts = (void *)get_bus_priv(bus);

	if (ndev) {
		netif_tx_stop_all_queues(ndev);
		ts->base.tx_stopped = 1;
	}

	writel(0x0, ts->txqueue_wake);

	/* sync up tx queue status before generating interrupt */
	dma_wmb();

	/* send irq to card: tx stopped */
	writel(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_STOP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));

	/* schedule reclaim attempt */
	tasklet_hi_schedule(&ts->base.reclaim_tq);
}