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
struct hnae3_handle {int /*<<< orphan*/  reset_level; scalar_t__ last_reset_time; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int /*<<< orphan*/  reset_request; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_FUNC_RESET ; 
 int /*<<< orphan*/  HNAE3_GLOBAL_RESET ; 
 int HZ ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_reset_task_schedule (struct hclge_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hclge_reset_event(struct hnae3_handle *handle)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	/* check if this is a new reset request and we are not here just because
	 * last reset attempt did not succeed and watchdog hit us again. We will
	 * know this if last reset request did not occur very recently (watchdog
	 * timer = 5*HZ, let us check after sufficiently large time, say 4*5*Hz)
	 * In case of new request we reset the "reset level" to PF reset.
	 * And if it is a repeat reset request of the most recent one then we
	 * want to make sure we throttle the reset request. Therefore, we will
	 * not allow it again before 3*HZ times.
	 */
	if (time_before(jiffies, (handle->last_reset_time + 3 * HZ)))
		return;
	else if (time_after(jiffies, (handle->last_reset_time + 4 * 5 * HZ)))
		handle->reset_level = HNAE3_FUNC_RESET;

	dev_info(&hdev->pdev->dev, "received reset event , reset type is %d",
		 handle->reset_level);

	/* request reset & schedule reset task */
	set_bit(handle->reset_level, &hdev->reset_request);
	hclge_reset_task_schedule(hdev);

	if (handle->reset_level < HNAE3_GLOBAL_RESET)
		handle->reset_level++;
}