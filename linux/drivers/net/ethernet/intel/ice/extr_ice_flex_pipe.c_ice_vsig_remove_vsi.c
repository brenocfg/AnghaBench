#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ice_vsig_vsi {size_t vsig; int changed; struct ice_vsig_vsi* next_vsi; } ;
struct ice_hw {TYPE_3__* blk; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_5__ {struct ice_vsig_vsi* vsis; TYPE_1__* vsig_tbl; } ;
struct TYPE_6__ {TYPE_2__ xlt2; } ;
struct TYPE_4__ {struct ice_vsig_vsi* first_vsi; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 size_t ICE_DEFAULT_VSIG ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 int ICE_ERR_PARAM ; 
 size_t ICE_MAX_VSI ; 
 size_t ICE_MAX_VSIGS ; 
 size_t ICE_VSIG_IDX_M ; 

__attribute__((used)) static enum ice_status
ice_vsig_remove_vsi(struct ice_hw *hw, enum ice_block blk, u16 vsi, u16 vsig)
{
	struct ice_vsig_vsi **vsi_head, *vsi_cur, *vsi_tgt;
	u16 idx;

	idx = vsig & ICE_VSIG_IDX_M;

	if (vsi >= ICE_MAX_VSI || idx >= ICE_MAX_VSIGS)
		return ICE_ERR_PARAM;

	if (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use)
		return ICE_ERR_DOES_NOT_EXIST;

	/* entry already in default VSIG, don't have to remove */
	if (idx == ICE_DEFAULT_VSIG)
		return 0;

	vsi_head = &hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	if (!(*vsi_head))
		return ICE_ERR_CFG;

	vsi_tgt = &hw->blk[blk].xlt2.vsis[vsi];
	vsi_cur = (*vsi_head);

	/* iterate the VSI list, skip over the entry to be removed */
	while (vsi_cur) {
		if (vsi_tgt == vsi_cur) {
			(*vsi_head) = vsi_cur->next_vsi;
			break;
		}
		vsi_head = &vsi_cur->next_vsi;
		vsi_cur = vsi_cur->next_vsi;
	}

	/* verify if VSI was removed from group list */
	if (!vsi_cur)
		return ICE_ERR_DOES_NOT_EXIST;

	vsi_cur->vsig = ICE_DEFAULT_VSIG;
	vsi_cur->changed = 1;
	vsi_cur->next_vsi = NULL;

	return 0;
}