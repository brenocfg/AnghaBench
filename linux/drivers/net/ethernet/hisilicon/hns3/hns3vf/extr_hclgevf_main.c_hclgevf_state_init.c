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
struct TYPE_2__ {int /*<<< orphan*/  mbx_mutex; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; TYPE_1__ mbx_resp; int /*<<< orphan*/  rst_service_task; int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  mbx_service_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGEVF_STATE_MBX_HANDLING ; 
 int /*<<< orphan*/  HCLGEVF_STATE_MBX_SERVICE_SCHED ; 
 int /*<<< orphan*/  HCLGEVF_STATE_SERVICE_SCHED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclgevf_mailbox_service_task ; 
 int /*<<< orphan*/  hclgevf_reset_service_task ; 
 int /*<<< orphan*/  hclgevf_service_task ; 
 int /*<<< orphan*/  hclgevf_service_timer ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_state_init(struct hclgevf_dev *hdev)
{
	/* setup tasks for the MBX */
	INIT_WORK(&hdev->mbx_service_task, hclgevf_mailbox_service_task);
	clear_bit(HCLGEVF_STATE_MBX_SERVICE_SCHED, &hdev->state);
	clear_bit(HCLGEVF_STATE_MBX_HANDLING, &hdev->state);

	/* setup tasks for service timer */
	timer_setup(&hdev->service_timer, hclgevf_service_timer, 0);

	INIT_WORK(&hdev->service_task, hclgevf_service_task);
	clear_bit(HCLGEVF_STATE_SERVICE_SCHED, &hdev->state);

	INIT_WORK(&hdev->rst_service_task, hclgevf_reset_service_task);

	mutex_init(&hdev->mbx_resp.mbx_mutex);

	/* bring the device down */
	set_bit(HCLGEVF_STATE_DOWN, &hdev->state);
}