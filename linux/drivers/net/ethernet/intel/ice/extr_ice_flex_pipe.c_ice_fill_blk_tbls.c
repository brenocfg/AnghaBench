#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ice_hw {TYPE_6__* blk; } ;
typedef  enum ice_block { ____Placeholder_ice_block } ice_block ;
struct TYPE_11__ {int /*<<< orphan*/  sid; } ;
struct TYPE_10__ {int /*<<< orphan*/  sid; } ;
struct TYPE_9__ {int /*<<< orphan*/  sid; } ;
struct TYPE_8__ {int /*<<< orphan*/  sid; } ;
struct TYPE_7__ {int /*<<< orphan*/  sid; } ;
struct TYPE_12__ {TYPE_5__ es; TYPE_4__ prof_redir; TYPE_3__ prof; TYPE_2__ xlt2; TYPE_1__ xlt1; } ;

/* Variables and functions */
 scalar_t__ ICE_BLK_COUNT ; 
 int /*<<< orphan*/  ice_fill_tbl (struct ice_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_init_sw_db (struct ice_hw*) ; 

void ice_fill_blk_tbls(struct ice_hw *hw)
{
	u8 i;

	for (i = 0; i < ICE_BLK_COUNT; i++) {
		enum ice_block blk_id = (enum ice_block)i;

		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].xlt1.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].xlt2.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].prof.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].prof_redir.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].es.sid);
	}

	ice_init_sw_db(hw);
}