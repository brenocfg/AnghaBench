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
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,char*,scalar_t__) ; 
 scalar_t__ bnx2x_flr_clnup_reg_poll (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int bnx2x_flr_clnup_poll_hw_counter(struct bnx2x *bp, u32 reg,
				    char *msg, u32 poll_cnt)
{
	u32 val = bnx2x_flr_clnup_reg_poll(bp, reg, 0, poll_cnt);
	if (val != 0) {
		BNX2X_ERR("%s usage count=%d\n", msg, val);
		return 1;
	}
	return 0;
}