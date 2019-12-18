#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_pf {TYPE_4__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  vlan_id; } ;
struct TYPE_6__ {TYPE_1__ vlan; } ;
struct TYPE_7__ {int /*<<< orphan*/  src_id; int /*<<< orphan*/  flag; TYPE_2__ l_data; int /*<<< orphan*/  fltr_act; int /*<<< orphan*/  vsi_handle; int /*<<< orphan*/  lkup_type; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; TYPE_3__ fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 int /*<<< orphan*/  ICE_SRC_ID_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_remove_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

int ice_vsi_kill_vlan(struct ice_vsi *vsi, u16 vid)
{
	struct ice_fltr_list_entry *list;
	struct ice_pf *pf = vsi->back;
	LIST_HEAD(tmp_add_list);
	enum ice_status status;
	int err = 0;

	list = devm_kzalloc(&pf->pdev->dev, sizeof(*list), GFP_KERNEL);
	if (!list)
		return -ENOMEM;

	list->fltr_info.lkup_type = ICE_SW_LKUP_VLAN;
	list->fltr_info.vsi_handle = vsi->idx;
	list->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	list->fltr_info.l_data.vlan.vlan_id = vid;
	list->fltr_info.flag = ICE_FLTR_TX;
	list->fltr_info.src_id = ICE_SRC_ID_VSI;

	INIT_LIST_HEAD(&list->list_entry);
	list_add(&list->list_entry, &tmp_add_list);

	status = ice_remove_vlan(&pf->hw, &tmp_add_list);
	if (status == ICE_ERR_DOES_NOT_EXIST) {
		dev_dbg(&pf->pdev->dev,
			"Failed to remove VLAN %d on VSI %i, it does not exist, status: %d\n",
			vid, vsi->vsi_num, status);
	} else if (status) {
		dev_err(&pf->pdev->dev,
			"Error removing VLAN %d on vsi %i error: %d\n",
			vid, vsi->vsi_num, status);
		err = -EIO;
	}

	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
	return err;
}