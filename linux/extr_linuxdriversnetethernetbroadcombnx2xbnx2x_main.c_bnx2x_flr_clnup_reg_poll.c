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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLR_WAIT_INTERVAL ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bnx2x_flr_clnup_reg_poll(struct bnx2x *bp, u32 reg,
				    u32 expected, u32 poll_count)
{
	u32 cur_cnt = poll_count;
	u32 val;

	while ((val = REG_RD(bp, reg)) != expected && cur_cnt--)
		udelay(FLR_WAIT_INTERVAL);

	return val;
}