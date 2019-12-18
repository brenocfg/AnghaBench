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
struct hclge_vport_vlan_cfg {int hd_tbl_status; int /*<<< orphan*/  node; int /*<<< orphan*/  vlan_id; } ;
struct hclge_vport {int /*<<< orphan*/  vlan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hclge_vport_vlan_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_add_vport_vlan_table(struct hclge_vport *vport, u16 vlan_id,
				       bool writen_to_tbl)
{
	struct hclge_vport_vlan_cfg *vlan;

	vlan = kzalloc(sizeof(*vlan), GFP_KERNEL);
	if (!vlan)
		return;

	vlan->hd_tbl_status = writen_to_tbl;
	vlan->vlan_id = vlan_id;

	list_add_tail(&vlan->node, &vport->vlan_list);
}