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
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {scalar_t__ wq; TYPE_1__ wk; } ;
struct lio {TYPE_2__ rxq_status_wq; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 

void cleanup_rx_oom_poll_fn(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);

	if (lio->rxq_status_wq.wq) {
		cancel_delayed_work_sync(&lio->rxq_status_wq.wk.work);
		flush_workqueue(lio->rxq_status_wq.wq);
		destroy_workqueue(lio->rxq_status_wq.wq);
	}
}