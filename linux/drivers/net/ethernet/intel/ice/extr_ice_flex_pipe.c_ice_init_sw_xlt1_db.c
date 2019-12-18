#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct ice_hw {TYPE_2__* blk; } ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_3__ {size_t count; scalar_t__* t; } ;
struct TYPE_4__ {TYPE_1__ xlt1; } ;

/* Variables and functions */
 scalar_t__ ICE_DEFAULT_PTG ; 
 int /*<<< orphan*/  ice_ptg_add_mv_ptype (struct ice_hw*,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ice_ptg_alloc_val (struct ice_hw*,int,scalar_t__) ; 

__attribute__((used)) static void ice_init_sw_xlt1_db(struct ice_hw *hw, enum ice_block blk)
{
	u16 pt;

	for (pt = 0; pt < hw->blk[blk].xlt1.count; pt++) {
		u8 ptg;

		ptg = hw->blk[blk].xlt1.t[pt];
		if (ptg != ICE_DEFAULT_PTG) {
			ice_ptg_alloc_val(hw, blk, ptg);
			ice_ptg_add_mv_ptype(hw, blk, pt, ptg);
		}
	}
}