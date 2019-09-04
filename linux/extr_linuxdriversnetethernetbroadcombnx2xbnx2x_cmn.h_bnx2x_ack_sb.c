#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bnx2x {scalar_t__ igu_dsb_id; TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ATTENTION_ID ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bnx2x*) ; 
 scalar_t__ IGU_SEG_ACCESS_ATTN ; 
 scalar_t__ IGU_SEG_ACCESS_DEF ; 
 scalar_t__ INT_BLOCK_HC ; 
 int /*<<< orphan*/  bnx2x_hc_ack_sb (struct bnx2x*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_igu_ack_sb (struct bnx2x*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void bnx2x_ack_sb(struct bnx2x *bp, u8 igu_sb_id, u8 storm,
				u16 index, u8 op, u8 update)
{
	if (bp->common.int_block == INT_BLOCK_HC)
		bnx2x_hc_ack_sb(bp, igu_sb_id, storm, index, op, update);
	else {
		u8 segment;

		if (CHIP_INT_MODE_IS_BC(bp))
			segment = storm;
		else if (igu_sb_id != bp->igu_dsb_id)
			segment = IGU_SEG_ACCESS_DEF;
		else if (storm == ATTENTION_ID)
			segment = IGU_SEG_ACCESS_ATTN;
		else
			segment = IGU_SEG_ACCESS_DEF;
		bnx2x_igu_ack_sb(bp, igu_sb_id, segment, index, op, update);
	}
}