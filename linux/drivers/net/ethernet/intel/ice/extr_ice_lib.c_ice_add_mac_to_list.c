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
typedef  int /*<<< orphan*/  u8 ;
struct list_head {int dummy; } ;
struct ice_vsi {int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_7__ {TYPE_2__ mac; } ;
struct TYPE_8__ {TYPE_3__ l_data; int /*<<< orphan*/  vsi_handle; int /*<<< orphan*/  fltr_act; int /*<<< orphan*/  lkup_type; int /*<<< orphan*/  src_id; int /*<<< orphan*/  flag; } ;
struct ice_fltr_list_entry {int /*<<< orphan*/  list_entry; TYPE_4__ fltr_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 int /*<<< orphan*/  ICE_SRC_ID_VSI ; 
 int /*<<< orphan*/  ICE_SW_LKUP_MAC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ice_fltr_list_entry* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

int ice_add_mac_to_list(struct ice_vsi *vsi, struct list_head *add_list,
			const u8 *macaddr)
{
	struct ice_fltr_list_entry *tmp;
	struct ice_pf *pf = vsi->back;

	tmp = devm_kzalloc(&pf->pdev->dev, sizeof(*tmp), GFP_ATOMIC);
	if (!tmp)
		return -ENOMEM;

	tmp->fltr_info.flag = ICE_FLTR_TX;
	tmp->fltr_info.src_id = ICE_SRC_ID_VSI;
	tmp->fltr_info.lkup_type = ICE_SW_LKUP_MAC;
	tmp->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	tmp->fltr_info.vsi_handle = vsi->idx;
	ether_addr_copy(tmp->fltr_info.l_data.mac.mac_addr, macaddr);

	INIT_LIST_HEAD(&tmp->list_entry);
	list_add(&tmp->list_entry, add_list);

	return 0;
}