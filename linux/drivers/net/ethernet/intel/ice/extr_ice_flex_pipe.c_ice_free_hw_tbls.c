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
typedef  size_t u8 ;
struct ice_hw {TYPE_6__* blk; } ;
struct TYPE_11__ {int /*<<< orphan*/  written; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  t; } ;
struct TYPE_10__ {int /*<<< orphan*/  t; } ;
struct TYPE_9__ {int /*<<< orphan*/  t; } ;
struct TYPE_8__ {int /*<<< orphan*/  vsis; int /*<<< orphan*/  vsig_tbl; int /*<<< orphan*/  t; } ;
struct TYPE_7__ {int /*<<< orphan*/  t; int /*<<< orphan*/  ptg_tbl; int /*<<< orphan*/  ptypes; } ;
struct TYPE_12__ {int is_list_init; TYPE_5__ es; TYPE_4__ prof_redir; TYPE_3__ prof; TYPE_2__ xlt2; TYPE_1__ xlt1; } ;

/* Variables and functions */
 size_t ICE_BLK_COUNT ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void ice_free_hw_tbls(struct ice_hw *hw)
{
	u8 i;

	for (i = 0; i < ICE_BLK_COUNT; i++) {
		hw->blk[i].is_list_init = false;

		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt1.ptypes);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt1.ptg_tbl);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt1.t);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt2.t);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt2.vsig_tbl);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].xlt2.vsis);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].prof.t);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].prof_redir.t);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].es.t);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].es.ref_count);
		devm_kfree(ice_hw_to_dev(hw), hw->blk[i].es.written);
	}

	memset(hw->blk, 0, sizeof(hw->blk));
}