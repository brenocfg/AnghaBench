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
struct hclgevf_dev {int /*<<< orphan*/  reset_state; scalar_t__ mbx_event_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_RESET_PENDING ; 
 int /*<<< orphan*/  hclgevf_mbx_task_schedule (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_reset_task_schedule (struct hclgevf_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_deferred_task_schedule(struct hclgevf_dev *hdev)
{
	/* if we have any pending mailbox event then schedule the mbx task */
	if (hdev->mbx_event_pending)
		hclgevf_mbx_task_schedule(hdev);

	if (test_bit(HCLGEVF_RESET_PENDING, &hdev->reset_state))
		hclgevf_reset_task_schedule(hdev);
}