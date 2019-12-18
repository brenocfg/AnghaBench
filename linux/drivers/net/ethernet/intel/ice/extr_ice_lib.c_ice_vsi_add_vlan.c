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
struct TYPE_7__ {TYPE_2__ l_data; int /*<<< orphan*/  vsi_handle; int /*<<< orphan*/  src_id; int /*<<< orphan*/  flag; int /*<<< orphan*/  fltr_act; int /*<<< orphan*/  lkup_type; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; TYPE_3__ fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 int /*<<< orphan*/  ICE_SRC_ID_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_add_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

int ice_vsi_add_vlan(struct ice_vsi *vsi, u16 vid)
{
	struct ice_fltr_list_entry *tmp;
	struct ice_pf *pf = vsi->back;
	LIST_HEAD(tmp_add_list);
	enum ice_status status;
	int err = 0;

	tmp = devm_kzalloc(&pf->pdev->dev, sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	tmp->fltr_info.lkup_type = ICE_SW_LKUP_VLAN;
	tmp->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	tmp->fltr_info.flag = ICE_FLTR_TX;
	tmp->fltr_info.src_id = ICE_SRC_ID_VSI;
	tmp->fltr_info.vsi_handle = vsi->idx;
	tmp->fltr_info.l_data.vlan.vlan_id = vid;

	INIT_LIST_HEAD(&tmp->list_entry);
	list_add(&tmp->list_entry, &tmp_add_list);

	status = ice_add_vlan(&pf->hw, &tmp_add_list);
	if (status) {
		err = -ENODEV;
		dev_err(&pf->pdev->dev, "Failure Adding VLAN %d on VSI %i\n",
			vid, vsi->vsi_num);
	}

	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
	return err;
}