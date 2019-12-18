#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hclge_dev {int /*<<< orphan*/  rst_service_task; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_REMOVING ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_SERVICE_SCHED ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_reset_task_schedule(struct hclge_dev *hdev)
{
	if (!test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGE_STATE_RST_SERVICE_SCHED, &hdev->state))
		queue_work_on(cpumask_first(&hdev->affinity_mask), system_wq,
			      &hdev->rst_service_task);
}