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
struct hclge_vport {int alloc_tqps; struct hclge_dev* back; } ;
struct hclge_dev {int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 int /*<<< orphan*/  HCLGE_STATE_SERVICE_SCHED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_cfg_mac_mode (struct hclge_dev*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_mac_stop_phy (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_tqp_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_tqp_enable (struct hclge_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_update_link_status (struct hclge_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_ae_stop(struct hnae3_handle *handle)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int i;

	set_bit(HCLGE_STATE_DOWN, &hdev->state);

	del_timer_sync(&hdev->service_timer);
	cancel_work_sync(&hdev->service_task);
	clear_bit(HCLGE_STATE_SERVICE_SCHED, &hdev->state);

	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state)) {
		hclge_mac_stop_phy(hdev);
		return;
	}

	for (i = 0; i < vport->alloc_tqps; i++)
		hclge_tqp_enable(hdev, i, 0, false);

	/* Mac disable */
	hclge_cfg_mac_mode(hdev, false);

	hclge_mac_stop_phy(hdev);

	/* reset tqp stats */
	hclge_reset_tqp_stats(handle);
	del_timer_sync(&hdev->service_timer);
	cancel_work_sync(&hdev->service_task);
	hclge_update_link_status(hdev);
}