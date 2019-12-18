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
struct octeon_device {int num_oqs; } ;
struct net_device {int dummy; } ;
struct lio {struct cavium_wq* rxq_status_wq; struct octeon_device* oct_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct cavium_wq {int /*<<< orphan*/ * wq; TYPE_1__ wk; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

void cleanup_rx_oom_poll_fn(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct cavium_wq *wq;
	int q_no;

	for (q_no = 0; q_no < oct->num_oqs; q_no++) {
		wq = &lio->rxq_status_wq[q_no];
		if (wq->wq) {
			cancel_delayed_work_sync(&wq->wk.work);
			flush_workqueue(wq->wq);
			destroy_workqueue(wq->wq);
			wq->wq = NULL;
		}
	}
}