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
struct octeon_droq {size_t q_no; } ;
struct octeon_device {TYPE_1__* props; } ;
struct net_device {int dummy; } ;
struct lio {struct cavium_wq* rxq_status_wq; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct cavium_wq {TYPE_2__ wk; int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  LIO_OOM_POLL_INTERVAL_MS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void octeon_schedule_rxq_oom_work(struct octeon_device *oct,
				  struct octeon_droq *droq)
{
	struct net_device *netdev = oct->props[0].netdev;
	struct lio *lio = GET_LIO(netdev);
	struct cavium_wq *wq = &lio->rxq_status_wq[droq->q_no];

	queue_delayed_work(wq->wq, &wq->wk.work,
			   msecs_to_jiffies(LIO_OOM_POLL_INTERVAL_MS));
}