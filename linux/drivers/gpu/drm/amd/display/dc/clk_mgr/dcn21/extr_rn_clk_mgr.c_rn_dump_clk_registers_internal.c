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
struct rn_clk_internal {void* CLK1_CLK0_BYPASS_CNTL; void* CLK1_CLK0_CURRENT_CNT; void* CLK1_CLK2_BYPASS_CNTL; void* CLK1_CLK2_CURRENT_CNT; void* CLK1_CLK1_BYPASS_CNTL; void* CLK1_CLK1_CURRENT_CNT; void* CLK1_CLK3_ALLOW_DS; void* CLK1_CLK3_DS_CNTL; void* CLK1_CLK3_BYPASS_CNTL; void* CLK1_CLK3_CURRENT_CNT; } ;
struct clk_mgr_internal {int dummy; } ;
struct clk_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK1_CLK0_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK1_CLK0_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK1_CLK1_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK1_CLK1_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK1_CLK2_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK1_CLK2_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK1_CLK3_ALLOW_DS ; 
 int /*<<< orphan*/  CLK1_CLK3_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK1_CLK3_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK1_CLK3_DS_CNTL ; 
 void* REG_READ (int /*<<< orphan*/ ) ; 
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 

__attribute__((used)) static void rn_dump_clk_registers_internal(struct rn_clk_internal *internal, struct clk_mgr *clk_mgr_base)
{
	struct clk_mgr_internal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	internal->CLK1_CLK3_CURRENT_CNT = REG_READ(CLK1_CLK3_CURRENT_CNT);
	internal->CLK1_CLK3_BYPASS_CNTL = REG_READ(CLK1_CLK3_BYPASS_CNTL);

	internal->CLK1_CLK3_DS_CNTL = REG_READ(CLK1_CLK3_DS_CNTL);	//dcf deep sleep divider
	internal->CLK1_CLK3_ALLOW_DS = REG_READ(CLK1_CLK3_ALLOW_DS);

	internal->CLK1_CLK1_CURRENT_CNT = REG_READ(CLK1_CLK1_CURRENT_CNT);
	internal->CLK1_CLK1_BYPASS_CNTL = REG_READ(CLK1_CLK1_BYPASS_CNTL);

	internal->CLK1_CLK2_CURRENT_CNT = REG_READ(CLK1_CLK2_CURRENT_CNT);
	internal->CLK1_CLK2_BYPASS_CNTL = REG_READ(CLK1_CLK2_BYPASS_CNTL);

	internal->CLK1_CLK0_CURRENT_CNT = REG_READ(CLK1_CLK0_CURRENT_CNT);
	internal->CLK1_CLK0_BYPASS_CNTL = REG_READ(CLK1_CLK0_BYPASS_CNTL);
}