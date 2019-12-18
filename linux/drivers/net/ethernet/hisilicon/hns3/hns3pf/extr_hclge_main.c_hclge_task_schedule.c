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
struct TYPE_2__ {int /*<<< orphan*/  stats_timer; } ;
struct hclge_dev {int /*<<< orphan*/  service_task; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  fd_arfs_expire_timer; TYPE_1__ hw_stats; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGE_STATE_REMOVING ; 
 int /*<<< orphan*/  HCLGE_STATE_SERVICE_SCHED ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hclge_task_schedule(struct hclge_dev *hdev, unsigned long delay_time)
{
	if (!test_bit(HCLGE_STATE_DOWN, &hdev->state) &&
	    !test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGE_STATE_SERVICE_SCHED, &hdev->state)) {
		hdev->hw_stats.stats_timer++;
		hdev->fd_arfs_expire_timer++;
		mod_delayed_work_on(cpumask_first(&hdev->affinity_mask),
				    system_wq, &hdev->service_task,
				    delay_time);
	}
}