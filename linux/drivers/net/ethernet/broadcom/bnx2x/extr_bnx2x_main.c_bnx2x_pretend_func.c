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
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 int /*<<< orphan*/  E1H_FUNC_MAX ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_get_pretend_reg (struct bnx2x*) ; 

int bnx2x_pretend_func(struct bnx2x *bp, u16 pretend_func_val)
{
	u32 pretend_reg;

	if (CHIP_IS_E1H(bp) && pretend_func_val >= E1H_FUNC_MAX)
		return -1;

	/* get my own pretend register */
	pretend_reg = bnx2x_get_pretend_reg(bp);
	REG_WR(bp, pretend_reg, pretend_func_val);
	REG_RD(bp, pretend_reg);
	return 0;
}