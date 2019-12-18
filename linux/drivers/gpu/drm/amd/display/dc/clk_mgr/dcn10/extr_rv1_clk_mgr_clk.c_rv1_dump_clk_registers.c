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
struct clk_state_registers {int CLK0_CLK8_CURRENT_CNT; int CLK0_CLK8_DS_CNTL; int CLK0_CLK8_ALLOW_DS; int CLK0_CLK10_CURRENT_CNT; int CLK0_CLK11_CURRENT_CNT; } ;
struct clk_mgr_internal {int dummy; } ;
struct clk_mgr {int dummy; } ;
struct clk_bypass {int dcfclk_bypass; int dispclk_pypass; int dprefclk_bypass; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK0_CLK10_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK0_CLK10_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK0_CLK11_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK0_CLK11_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK0_CLK8_ALLOW_DS ; 
 int /*<<< orphan*/  CLK0_CLK8_BYPASS_CNTL ; 
 int /*<<< orphan*/  CLK0_CLK8_CURRENT_CNT ; 
 int /*<<< orphan*/  CLK0_CLK8_DS_CNTL ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 

void rv1_dump_clk_registers(struct clk_state_registers *regs, struct clk_bypass *bypass, struct clk_mgr *clk_mgr_base)
{
	struct clk_mgr_internal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

		regs->CLK0_CLK8_CURRENT_CNT = REG_READ(CLK0_CLK8_CURRENT_CNT) / 10; //dcf clk

		bypass->dcfclk_bypass = REG_READ(CLK0_CLK8_BYPASS_CNTL) & 0x0007;
		if (bypass->dcfclk_bypass < 0 || bypass->dcfclk_bypass > 4)
			bypass->dcfclk_bypass = 0;


		regs->CLK0_CLK8_DS_CNTL = REG_READ(CLK0_CLK8_DS_CNTL) / 10;	//dcf deep sleep divider

		regs->CLK0_CLK8_ALLOW_DS = REG_READ(CLK0_CLK8_ALLOW_DS); //dcf deep sleep allow

		regs->CLK0_CLK10_CURRENT_CNT = REG_READ(CLK0_CLK10_CURRENT_CNT) / 10; //dpref clk

		bypass->dispclk_pypass = REG_READ(CLK0_CLK10_BYPASS_CNTL) & 0x0007;
		if (bypass->dispclk_pypass < 0 || bypass->dispclk_pypass > 4)
			bypass->dispclk_pypass = 0;

		regs->CLK0_CLK11_CURRENT_CNT = REG_READ(CLK0_CLK11_CURRENT_CNT) / 10; //disp clk

		bypass->dprefclk_bypass = REG_READ(CLK0_CLK11_BYPASS_CNTL) & 0x0007;
		if (bypass->dprefclk_bypass < 0 || bypass->dprefclk_bypass > 4)
			bypass->dprefclk_bypass = 0;

}