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
struct TYPE_4__ {scalar_t__ func; } ;
struct TYPE_3__ {scalar_t__ function; } ;
struct hclge_dev {TYPE_2__ mbx_service_task; TYPE_2__ rst_service_task; TYPE_2__ service_task; TYPE_1__ service_timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  cancel_work_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_state_uninit(struct hclge_dev *hdev)
{
	set_bit(HCLGE_STATE_DOWN, &hdev->state);

	if (hdev->service_timer.function)
		del_timer_sync(&hdev->service_timer);
	if (hdev->service_task.func)
		cancel_work_sync(&hdev->service_task);
	if (hdev->rst_service_task.func)
		cancel_work_sync(&hdev->rst_service_task);
	if (hdev->mbx_service_task.func)
		cancel_work_sync(&hdev->mbx_service_task);
}