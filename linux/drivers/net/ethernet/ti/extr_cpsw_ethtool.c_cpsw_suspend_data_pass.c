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
struct TYPE_3__ {int slaves; } ;
struct cpsw_common {int /*<<< orphan*/  dma; TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_intr_disable (struct cpsw_common*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void cpsw_suspend_data_pass(struct net_device *ndev)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	int i;

	/* Disable NAPI scheduling */
	cpsw_intr_disable(cpsw);

	/* Stop all transmit queues for every network device.
	 */
	for (i = 0; i < cpsw->data.slaves; i++) {
		ndev = cpsw->slaves[i].ndev;
		if (!(ndev && netif_running(ndev)))
			continue;

		netif_tx_stop_all_queues(ndev);

		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb__after_atomic();
	}

	/* Handle rest of tx packets and stop cpdma channels */
	cpdma_ctlr_stop(cpsw->dma);
}