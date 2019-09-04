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
struct hclge_dev {int /*<<< orphan*/  service_task; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGE_STATE_REMOVING ; 
 int /*<<< orphan*/  HCLGE_STATE_SERVICE_SCHED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_task_schedule(struct hclge_dev *hdev)
{
	if (!test_bit(HCLGE_STATE_DOWN, &hdev->state) &&
	    !test_bit(HCLGE_STATE_REMOVING, &hdev->state) &&
	    !test_and_set_bit(HCLGE_STATE_SERVICE_SCHED, &hdev->state))
		(void)schedule_work(&hdev->service_task);
}