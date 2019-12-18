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
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {scalar_t__ port_base_vlan_state; } ;
struct hclge_vport {int /*<<< orphan*/  vlan_del_fail_bmap; int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_dev {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 scalar_t__ HNAE3_PORT_BASE_VLAN_DISABLE ; 
 int /*<<< orphan*/  hclge_add_vport_vlan_table (struct hclge_vport*,int /*<<< orphan*/ ,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_rm_vport_vlan_table (struct hclge_vport*,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vlan_filter_hw (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hclge_set_vlan_filter(struct hnae3_handle *handle, __be16 proto,
			  u16 vlan_id, bool is_kill)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	bool writen_to_tbl = false;
	int ret = 0;

	/* When device is resetting, firmware is unable to handle
	 * mailbox. Just record the vlan id, and remove it after
	 * reset finished.
	 */
	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) && is_kill) {
		set_bit(vlan_id, vport->vlan_del_fail_bmap);
		return -EBUSY;
	}

	/* when port base vlan enabled, we use port base vlan as the vlan
	 * filter entry. In this case, we don't update vlan filter table
	 * when user add new vlan or remove exist vlan, just update the vport
	 * vlan list. The vlan id in vlan list will be writen in vlan filter
	 * table until port base vlan disabled
	 */
	if (handle->port_base_vlan_state == HNAE3_PORT_BASE_VLAN_DISABLE) {
		ret = hclge_set_vlan_filter_hw(hdev, proto, vport->vport_id,
					       vlan_id, is_kill);
		writen_to_tbl = true;
	}

	if (!ret) {
		if (is_kill)
			hclge_rm_vport_vlan_table(vport, vlan_id, false);
		else
			hclge_add_vport_vlan_table(vport, vlan_id,
						   writen_to_tbl);
	} else if (is_kill) {
		/* when remove hw vlan filter failed, record the vlan id,
		 * and try to remove it from hw later, to be consistence
		 * with stack
		 */
		set_bit(vlan_id, vport->vlan_del_fail_bmap);
	}
	return ret;
}