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
struct ice_vsi {int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  ethtype; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_pf {TYPE_4__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  ethertype; } ;
struct TYPE_6__ {TYPE_1__ ethertype_mac; } ;
struct TYPE_7__ {TYPE_2__ l_data; int /*<<< orphan*/  vsi_handle; int /*<<< orphan*/  src_id; int /*<<< orphan*/  flag; int /*<<< orphan*/  fltr_act; int /*<<< orphan*/  lkup_type; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; TYPE_3__ fltr_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_DROP_PACKET ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_SRC_ID_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_ETHERTYPE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_add_eth_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_remove_eth_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

__attribute__((used)) static void
ice_vsi_add_rem_eth_mac(struct ice_vsi *vsi, bool add_rule)
{
	struct ice_fltr_list_entry *list;
	struct ice_pf *pf = vsi->back;
	LIST_HEAD(tmp_add_list);
	enum ice_status status;

	list = devm_kzalloc(&pf->pdev->dev, sizeof(*list), GFP_KERNEL);
	if (!list)
		return;

	list->fltr_info.lkup_type = ICE_SW_LKUP_ETHERTYPE;
	list->fltr_info.fltr_act = ICE_DROP_PACKET;
	list->fltr_info.flag = ICE_FLTR_TX;
	list->fltr_info.src_id = ICE_SRC_ID_VSI;
	list->fltr_info.vsi_handle = vsi->idx;
	list->fltr_info.l_data.ethertype_mac.ethertype = vsi->ethtype;

	INIT_LIST_HEAD(&list->list_entry);
	list_add(&list->list_entry, &tmp_add_list);

	if (add_rule)
		status = ice_add_eth_mac(&pf->hw, &tmp_add_list);
	else
		status = ice_remove_eth_mac(&pf->hw, &tmp_add_list);

	if (status)
		dev_err(&pf->pdev->dev,
			"Failure Adding or Removing Ethertype on VSI %i error: %d\n",
			vsi->vsi_num, status);

	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
}