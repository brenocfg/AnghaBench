#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct igu_ack_register {int sb_id_and_flags; int /*<<< orphan*/  status_block_index; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ COMMAND_REG_INT_ACK ; 
 scalar_t__ HC_REG_COMMAND_REG ; 
 int IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT ; 
 int IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT ; 
 int IGU_ACK_REGISTER_STORM_ID_SHIFT ; 
 int IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static inline void bnx2x_hc_ack_sb(struct bnx2x *bp, u8 sb_id,
				   u8 storm, u16 index, u8 op, u8 update)
{
	u32 hc_addr = (HC_REG_COMMAND_REG + BP_PORT(bp)*32 +
		       COMMAND_REG_INT_ACK);
	struct igu_ack_register igu_ack;

	igu_ack.status_block_index = index;
	igu_ack.sb_id_and_flags =
			((sb_id << IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT) |
			 (storm << IGU_ACK_REGISTER_STORM_ID_SHIFT) |
			 (update << IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT) |
			 (op << IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT));

	REG_WR(bp, hc_addr, (*(u32 *)&igu_ack));

	/* Make sure that ACK is written */
	barrier();
}