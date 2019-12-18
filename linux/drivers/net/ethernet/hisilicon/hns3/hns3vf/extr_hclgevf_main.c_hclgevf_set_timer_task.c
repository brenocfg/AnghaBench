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
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_SERVICE_SCHED ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void hclgevf_set_timer_task(struct hnae3_handle *handle, bool enable)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	if (enable) {
		mod_timer(&hdev->service_timer, jiffies + HZ);
	} else {
		del_timer_sync(&hdev->service_timer);
		cancel_work_sync(&hdev->service_task);
		clear_bit(HCLGEVF_STATE_SERVICE_SCHED, &hdev->state);
	}
}