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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct igu_regular {int sb_id_and_flags; int /*<<< orphan*/  member_0; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int IGU_REGULAR_BUPDATE_SHIFT ; 
 int IGU_REGULAR_ENABLE_INT_SHIFT ; 
 int IGU_REGULAR_SB_INDEX_SHIFT ; 
 int IGU_REGULAR_SEGMENT_ACCESS_SHIFT ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static inline void bnx2x_igu_ack_sb_gen(struct bnx2x *bp, u8 igu_sb_id,
					u8 segment, u16 index, u8 op,
					u8 update, u32 igu_addr)
{
	struct igu_regular cmd_data = {0};

	cmd_data.sb_id_and_flags =
			((index << IGU_REGULAR_SB_INDEX_SHIFT) |
			 (segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
			 (update << IGU_REGULAR_BUPDATE_SHIFT) |
			 (op << IGU_REGULAR_ENABLE_INT_SHIFT));

	DP(NETIF_MSG_INTR, "write 0x%08x to IGU addr 0x%x\n",
	   cmd_data.sb_id_and_flags, igu_addr);
	REG_WR(bp, igu_addr, cmd_data.sb_id_and_flags);

	/* Make sure that ACK is written */
	barrier();
}