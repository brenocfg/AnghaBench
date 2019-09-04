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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int PXP_REG_HST_ZONE_PERMISSION_TABLE ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 

__attribute__((used)) static void bnx2x_vf_qtbl_set_q(struct bnx2x *bp, u8 abs_vfid, u8 qid,
				u8 enable)
{
	u32 reg = PXP_REG_HST_ZONE_PERMISSION_TABLE + qid * 4;
	u32 val = enable ? (abs_vfid | (1 << 6)) : 0;

	REG_WR(bp, reg, val);
}