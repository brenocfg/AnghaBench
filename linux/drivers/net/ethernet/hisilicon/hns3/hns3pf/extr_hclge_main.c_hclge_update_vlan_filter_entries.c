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
typedef  scalar_t__ u16 ;
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_vlan_info {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  vlan_proto; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HNAE3_PORT_BASE_VLAN_ENABLE ; 
 int hclge_add_vport_all_vlan_table (struct hclge_vport*) ; 
 int /*<<< orphan*/  hclge_rm_vport_all_vlan_table (struct hclge_vport*,int) ; 
 int hclge_set_vlan_filter_hw (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_update_vlan_filter_entries(struct hclge_vport *vport,
					    u16 port_base_vlan_state,
					    struct hclge_vlan_info *new_info,
					    struct hclge_vlan_info *old_info)
{
	struct hclge_dev *hdev = vport->back;
	int ret;

	if (port_base_vlan_state == HNAE3_PORT_BASE_VLAN_ENABLE) {
		hclge_rm_vport_all_vlan_table(vport, false);
		return hclge_set_vlan_filter_hw(hdev,
						 htons(new_info->vlan_proto),
						 vport->vport_id,
						 new_info->vlan_tag,
						 false);
	}

	ret = hclge_set_vlan_filter_hw(hdev, htons(old_info->vlan_proto),
				       vport->vport_id, old_info->vlan_tag,
				       true);
	if (ret)
		return ret;

	return hclge_add_vport_all_vlan_table(vport);
}