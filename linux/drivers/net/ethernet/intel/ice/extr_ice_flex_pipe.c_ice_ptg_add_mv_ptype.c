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
typedef  size_t u8 ;
typedef  int u16 ;
struct ice_hw {TYPE_4__* blk; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_7__ {size_t* t; TYPE_2__* ptypes; TYPE_1__* ptg_tbl; } ;
struct TYPE_8__ {TYPE_3__ xlt1; } ;
struct TYPE_6__ {size_t ptg; struct TYPE_6__* next_ptype; } ;
struct TYPE_5__ {TYPE_2__* first_ptype; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 size_t ICE_DEFAULT_PTG ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 int ICE_ERR_PARAM ; 
 int ICE_XLT1_CNT ; 
 int ice_ptg_find_ptype (struct ice_hw*,int,int,size_t*) ; 
 int /*<<< orphan*/  ice_ptg_remove_ptype (struct ice_hw*,int,int,size_t) ; 

__attribute__((used)) static enum ice_status
ice_ptg_add_mv_ptype(struct ice_hw *hw, enum ice_block blk, u16 ptype, u8 ptg)
{
	enum ice_status status;
	u8 original_ptg;

	if (ptype > ICE_XLT1_CNT - 1)
		return ICE_ERR_PARAM;

	if (!hw->blk[blk].xlt1.ptg_tbl[ptg].in_use && ptg != ICE_DEFAULT_PTG)
		return ICE_ERR_DOES_NOT_EXIST;

	status = ice_ptg_find_ptype(hw, blk, ptype, &original_ptg);
	if (status)
		return status;

	/* Is ptype already in the correct PTG? */
	if (original_ptg == ptg)
		return 0;

	/* Remove from original PTG and move back to the default PTG */
	if (original_ptg != ICE_DEFAULT_PTG)
		ice_ptg_remove_ptype(hw, blk, ptype, original_ptg);

	/* Moving to default PTG? Then we're done with this request */
	if (ptg == ICE_DEFAULT_PTG)
		return 0;

	/* Add ptype to PTG at beginning of list */
	hw->blk[blk].xlt1.ptypes[ptype].next_ptype =
		hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype =
		&hw->blk[blk].xlt1.ptypes[ptype];

	hw->blk[blk].xlt1.ptypes[ptype].ptg = ptg;
	hw->blk[blk].xlt1.t[ptype] = ptg;

	return 0;
}