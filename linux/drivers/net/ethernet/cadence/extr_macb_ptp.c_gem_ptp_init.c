#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev; } ;
struct macb_queue {int /*<<< orphan*/  tx_ts_task; scalar_t__ tx_ts_tail; scalar_t__ tx_ts_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_adj; } ;
struct macb {unsigned int num_queues; TYPE_2__* pdev; struct macb_queue* queues; int /*<<< orphan*/  tsu_clk_lock; int /*<<< orphan*/ * ptp_clock; TYPE_3__ ptp_clock_info; TYPE_1__* ptp_info; int /*<<< orphan*/  tsu_rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_ptp_max_adj ) () ;int /*<<< orphan*/  (* get_tsu_rate ) (struct macb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_PTP_TIMER_NAME ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ gem_ptp_caps_template ; 
 int /*<<< orphan*/  gem_ptp_init_timer (struct macb*) ; 
 int /*<<< orphan*/  gem_ptp_init_tsu (struct macb*) ; 
 int /*<<< orphan*/  gem_tx_timestamp_flush ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct macb*) ; 
 int /*<<< orphan*/  stub2 () ; 

void gem_ptp_init(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	struct macb_queue *queue;
	unsigned int q;

	bp->ptp_clock_info = gem_ptp_caps_template;

	/* nominal frequency and maximum adjustment in ppb */
	bp->tsu_rate = bp->ptp_info->get_tsu_rate(bp);
	bp->ptp_clock_info.max_adj = bp->ptp_info->get_ptp_max_adj();
	gem_ptp_init_timer(bp);
	bp->ptp_clock = ptp_clock_register(&bp->ptp_clock_info, &dev->dev);
	if (IS_ERR(bp->ptp_clock)) {
		pr_err("ptp clock register failed: %ld\n",
			PTR_ERR(bp->ptp_clock));
		bp->ptp_clock = NULL;
		return;
	} else if (bp->ptp_clock == NULL) {
		pr_err("ptp clock register failed\n");
		return;
	}

	spin_lock_init(&bp->tsu_clk_lock);
	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		queue->tx_ts_head = 0;
		queue->tx_ts_tail = 0;
		INIT_WORK(&queue->tx_ts_task, gem_tx_timestamp_flush);
	}

	gem_ptp_init_tsu(bp);

	dev_info(&bp->pdev->dev, "%s ptp clock registered.\n",
		 GEM_PTP_TIMER_NAME);
}