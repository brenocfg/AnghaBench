#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mcp_attn_ctl_regs ; 

__attribute__((used)) static inline void bnx2x_set_mcp_parity(struct bnx2x *bp, u8 enable)
{
	int i;
	u32 reg_val;

	for (i = 0; i < ARRAY_SIZE(mcp_attn_ctl_regs); i++) {
		reg_val = REG_RD(bp, mcp_attn_ctl_regs[i].addr);

		if (enable)
			reg_val |= mcp_attn_ctl_regs[i].bits;
		else
			reg_val &= ~mcp_attn_ctl_regs[i].bits;

		REG_WR(bp, mcp_attn_ctl_regs[i].addr, reg_val);
	}
}