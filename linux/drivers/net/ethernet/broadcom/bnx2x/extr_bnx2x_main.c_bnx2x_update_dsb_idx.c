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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ running_index; } ;
struct TYPE_4__ {scalar_t__ attn_bits_index; } ;
struct host_sp_status_block {TYPE_1__ sp_sb; TYPE_2__ atten_status_block; } ;
struct bnx2x {scalar_t__ def_att_idx; scalar_t__ def_idx; struct host_sp_status_block* def_status_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEF_SB_ATT_IDX ; 
 int /*<<< orphan*/  BNX2X_DEF_SB_IDX ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static u16 bnx2x_update_dsb_idx(struct bnx2x *bp)
{
	struct host_sp_status_block *def_sb = bp->def_status_blk;
	u16 rc = 0;

	barrier(); /* status block is written to by the chip */
	if (bp->def_att_idx != def_sb->atten_status_block.attn_bits_index) {
		bp->def_att_idx = def_sb->atten_status_block.attn_bits_index;
		rc |= BNX2X_DEF_SB_ATT_IDX;
	}

	if (bp->def_idx != def_sb->sp_sb.running_index) {
		bp->def_idx = def_sb->sp_sb.running_index;
		rc |= BNX2X_DEF_SB_IDX;
	}

	/* Do not reorder: indices reading should complete before handling */
	barrier();
	return rc;
}