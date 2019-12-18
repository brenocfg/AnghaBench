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
typedef  scalar_t__ u16 ;
struct hnae3_handle {scalar_t__ port_base_vlan_state; } ;
struct hclge_vlan_info {int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan_tag; } ;
struct TYPE_2__ {struct hclge_vlan_info vlan_info; scalar_t__ state; } ;
struct hclge_vport {TYPE_1__ port_base_vlan_cfg; int /*<<< orphan*/  vport_id; struct hclge_dev* back; struct hnae3_handle nic; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HNAE3_PORT_BASE_VLAN_DISABLE ; 
 scalar_t__ HNAE3_PORT_BASE_VLAN_ENABLE ; 
 scalar_t__ HNAE3_PORT_BASE_VLAN_MODIFY ; 
 int hclge_set_vlan_filter_hw (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hclge_update_vlan_filter_entries (struct hclge_vport*,scalar_t__,struct hclge_vlan_info*,struct hclge_vlan_info*) ; 
 int hclge_vlan_offload_cfg (struct hclge_vport*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

int hclge_update_port_base_vlan_cfg(struct hclge_vport *vport, u16 state,
				    struct hclge_vlan_info *vlan_info)
{
	struct hnae3_handle *nic = &vport->nic;
	struct hclge_vlan_info *old_vlan_info;
	struct hclge_dev *hdev = vport->back;
	int ret;

	old_vlan_info = &vport->port_base_vlan_cfg.vlan_info;

	ret = hclge_vlan_offload_cfg(vport, state, vlan_info->vlan_tag);
	if (ret)
		return ret;

	if (state == HNAE3_PORT_BASE_VLAN_MODIFY) {
		/* add new VLAN tag */
		ret = hclge_set_vlan_filter_hw(hdev,
					       htons(vlan_info->vlan_proto),
					       vport->vport_id,
					       vlan_info->vlan_tag,
					       false);
		if (ret)
			return ret;

		/* remove old VLAN tag */
		ret = hclge_set_vlan_filter_hw(hdev,
					       htons(old_vlan_info->vlan_proto),
					       vport->vport_id,
					       old_vlan_info->vlan_tag,
					       true);
		if (ret)
			return ret;

		goto update;
	}

	ret = hclge_update_vlan_filter_entries(vport, state, vlan_info,
					       old_vlan_info);
	if (ret)
		return ret;

	/* update state only when disable/enable port based VLAN */
	vport->port_base_vlan_cfg.state = state;
	if (state == HNAE3_PORT_BASE_VLAN_DISABLE)
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_DISABLE;
	else
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_ENABLE;

update:
	vport->port_base_vlan_cfg.vlan_info.vlan_tag = vlan_info->vlan_tag;
	vport->port_base_vlan_cfg.vlan_info.qos = vlan_info->qos;
	vport->port_base_vlan_cfg.vlan_info.vlan_proto = vlan_info->vlan_proto;

	return 0;
}