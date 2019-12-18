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
struct TYPE_2__ {int num_tqps; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {scalar_t__ reset_type; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 scalar_t__ HNAE3_FUNC_RESET ; 
 int /*<<< orphan*/  hclge_cfg_mac_mode (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_clear_arfs_rules (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_config_mac_tnl_int (struct hclge_dev*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_mac_stop_phy (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_reset_tqp (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  hclge_reset_tqp_stats (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_update_link_status (struct hclge_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_ae_stop(struct hnae3_handle *handle)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int i;

	set_bit(HCLGE_STATE_DOWN, &hdev->state);

	hclge_clear_arfs_rules(handle);

	/* If it is not PF reset, the firmware will disable the MAC,
	 * so it only need to stop phy here.
	 */
	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) &&
	    hdev->reset_type != HNAE3_FUNC_RESET) {
		hclge_mac_stop_phy(hdev);
		hclge_update_link_status(hdev);
		return;
	}

	for (i = 0; i < handle->kinfo.num_tqps; i++)
		hclge_reset_tqp(handle, i);

	hclge_config_mac_tnl_int(hdev, false);

	/* Mac disable */
	hclge_cfg_mac_mode(hdev, false);

	hclge_mac_stop_phy(hdev);

	/* reset tqp stats */
	hclge_reset_tqp_stats(handle);
	hclge_update_link_status(hdev);
}