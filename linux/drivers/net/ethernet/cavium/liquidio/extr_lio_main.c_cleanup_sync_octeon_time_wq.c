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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct cavium_wq {scalar_t__ wq; TYPE_1__ wk; } ;
struct lio {struct cavium_wq sync_octeon_time_wq; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 

__attribute__((used)) static inline void cleanup_sync_octeon_time_wq(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);
	struct cavium_wq *time_wq = &lio->sync_octeon_time_wq;

	if (time_wq->wq) {
		cancel_delayed_work_sync(&time_wq->wk.work);
		destroy_workqueue(time_wq->wq);
	}
}