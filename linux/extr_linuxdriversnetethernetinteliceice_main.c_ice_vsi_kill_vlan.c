#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int /*<<< orphan*/  vsi_num; struct ice_pf* back; } ;
struct ice_pf {TYPE_5__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  vlan_id; } ;
struct TYPE_8__ {TYPE_2__ vlan; } ;
struct TYPE_6__ {int /*<<< orphan*/  vsi_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  src; int /*<<< orphan*/  flag; TYPE_3__ l_data; int /*<<< orphan*/  fltr_act; TYPE_1__ fwd_id; int /*<<< orphan*/  lkup_type; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; TYPE_4__ fltr_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_remove_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

__attribute__((used)) static void ice_vsi_kill_vlan(struct ice_vsi *vsi, u16 vid)
{
	struct ice_fltr_list_entry *list;
	struct ice_pf *pf = vsi->back;
	LIST_HEAD(tmp_add_list);

	list = devm_kzalloc(&pf->pdev->dev, sizeof(*list), GFP_KERNEL);
	if (!list)
		return;

	list->fltr_info.lkup_type = ICE_SW_LKUP_VLAN;
	list->fltr_info.fwd_id.vsi_id = vsi->vsi_num;
	list->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	list->fltr_info.l_data.vlan.vlan_id = vid;
	list->fltr_info.flag = ICE_FLTR_TX;
	list->fltr_info.src = vsi->vsi_num;

	INIT_LIST_HEAD(&list->list_entry);
	list_add(&list->list_entry, &tmp_add_list);

	if (ice_remove_vlan(&pf->hw, &tmp_add_list))
		dev_err(&pf->pdev->dev, "Error removing VLAN %d on vsi %i\n",
			vid, vsi->vsi_num);

	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
}