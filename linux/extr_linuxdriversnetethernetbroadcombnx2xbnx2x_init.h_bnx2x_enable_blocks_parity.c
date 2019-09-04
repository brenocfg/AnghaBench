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
typedef  int u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int en_mask; int /*<<< orphan*/  mask_addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* bnx2x_blocks_parity_data ; 
 int bnx2x_parity_reg_mask (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_set_mcp_parity (struct bnx2x*,int) ; 

__attribute__((used)) static inline void bnx2x_enable_blocks_parity(struct bnx2x *bp)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) {
		u32 reg_mask = bnx2x_parity_reg_mask(bp, i);

		if (reg_mask)
			REG_WR(bp, bnx2x_blocks_parity_data[i].mask_addr,
				bnx2x_blocks_parity_data[i].en_mask & reg_mask);
	}

	/* Enable MCP parity attentions */
	bnx2x_set_mcp_parity(bp, true);
}