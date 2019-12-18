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
struct ice_hw {TYPE_2__* blk; } ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_6__ {size_t count; size_t* t; TYPE_1__* vsis; } ;
struct TYPE_5__ {TYPE_3__ xlt2; } ;
struct TYPE_4__ {scalar_t__ changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_vsig_add_mv_vsi (struct ice_hw*,int,size_t,size_t) ; 
 int /*<<< orphan*/  ice_vsig_alloc_val (struct ice_hw*,int,size_t) ; 

__attribute__((used)) static void ice_init_sw_xlt2_db(struct ice_hw *hw, enum ice_block blk)
{
	u16 vsi;

	for (vsi = 0; vsi < hw->blk[blk].xlt2.count; vsi++) {
		u16 vsig;

		vsig = hw->blk[blk].xlt2.t[vsi];
		if (vsig) {
			ice_vsig_alloc_val(hw, blk, vsig);
			ice_vsig_add_mv_vsi(hw, blk, vsi, vsig);
			/* no changes at this time, since this has been
			 * initialized from the original package
			 */
			hw->blk[blk].xlt2.vsis[vsi].changed = 0;
		}
	}
}