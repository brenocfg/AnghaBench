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
typedef  size_t u8 ;
typedef  int u16 ;
struct ice_ptg_ptype {struct ice_ptg_ptype* next_ptype; int /*<<< orphan*/  ptg; } ;
struct ice_hw {TYPE_3__* blk; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_5__ {struct ice_ptg_ptype* ptypes; TYPE_1__* ptg_tbl; } ;
struct TYPE_6__ {TYPE_2__ xlt1; } ;
struct TYPE_4__ {struct ice_ptg_ptype* first_ptype; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DEFAULT_PTG ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 int ICE_ERR_PARAM ; 
 int ICE_XLT1_CNT ; 

__attribute__((used)) static enum ice_status
ice_ptg_remove_ptype(struct ice_hw *hw, enum ice_block blk, u16 ptype, u8 ptg)
{
	struct ice_ptg_ptype **ch;
	struct ice_ptg_ptype *p;

	if (ptype > ICE_XLT1_CNT - 1)
		return ICE_ERR_PARAM;

	if (!hw->blk[blk].xlt1.ptg_tbl[ptg].in_use)
		return ICE_ERR_DOES_NOT_EXIST;

	/* Should not happen if .in_use is set, bad config */
	if (!hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype)
		return ICE_ERR_CFG;

	/* find the ptype within this PTG, and bypass the link over it */
	p = hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	ch = &hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	while (p) {
		if (ptype == (p - hw->blk[blk].xlt1.ptypes)) {
			*ch = p->next_ptype;
			break;
		}

		ch = &p->next_ptype;
		p = p->next_ptype;
	}

	hw->blk[blk].xlt1.ptypes[ptype].ptg = ICE_DEFAULT_PTG;
	hw->blk[blk].xlt1.ptypes[ptype].next_ptype = NULL;

	return 0;
}