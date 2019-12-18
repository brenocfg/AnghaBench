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
struct rn_clk_internal {int CLK1_CLK3_CURRENT_CNT; int CLK1_CLK3_DS_CNTL; int CLK1_CLK3_ALLOW_DS; int CLK1_CLK2_CURRENT_CNT; int CLK1_CLK0_CURRENT_CNT; int CLK1_CLK1_CURRENT_CNT; int CLK1_CLK1_BYPASS_CNTL; int CLK1_CLK3_BYPASS_CNTL; int CLK1_CLK0_BYPASS_CNTL; int CLK1_CLK2_BYPASS_CNTL; int /*<<< orphan*/  member_0; } ;
struct clk_state_registers_and_bypass {int dcfclk; int dcf_deep_sleep_divider; int dcf_deep_sleep_allow; int dprefclk; int dispclk; int dppclk; int dppclk_bypass; int dcfclk_bypass; int dispclk_bypass; int dprefclk_bypass; } ;
struct clk_mgr {int dummy; } ;
struct clk_log_info {unsigned int bufSize; unsigned int pBuf; unsigned int* sum_chars_printed; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  rn_dump_clk_registers_internal (struct rn_clk_internal*,struct clk_mgr*) ; 
 unsigned int snprintf_count (unsigned int,unsigned int,char*,...) ; 

__attribute__((used)) static void rn_dump_clk_registers(struct clk_state_registers_and_bypass *regs_and_bypass,
		struct clk_mgr *clk_mgr_base, struct clk_log_info *log_info)
{
	struct rn_clk_internal internal = {0};
	char *bypass_clks[5] = {"0x0 DFS", "0x1 REFCLK", "0x2 ERROR", "0x3 400 FCH", "0x4 600 FCH"};
	unsigned int chars_printed = 0;
	unsigned int remaining_buffer = log_info->bufSize;

	rn_dump_clk_registers_internal(&internal, clk_mgr_base);

	regs_and_bypass->dcfclk = internal.CLK1_CLK3_CURRENT_CNT / 10;
	regs_and_bypass->dcf_deep_sleep_divider = internal.CLK1_CLK3_DS_CNTL / 10;
	regs_and_bypass->dcf_deep_sleep_allow = internal.CLK1_CLK3_ALLOW_DS;
	regs_and_bypass->dprefclk = internal.CLK1_CLK2_CURRENT_CNT / 10;
	regs_and_bypass->dispclk = internal.CLK1_CLK0_CURRENT_CNT / 10;
	regs_and_bypass->dppclk = internal.CLK1_CLK1_CURRENT_CNT / 10;

	regs_and_bypass->dppclk_bypass = internal.CLK1_CLK1_BYPASS_CNTL & 0x0007;
	if (regs_and_bypass->dppclk_bypass < 0 || regs_and_bypass->dppclk_bypass > 4)
		regs_and_bypass->dppclk_bypass = 0;
	regs_and_bypass->dcfclk_bypass = internal.CLK1_CLK3_BYPASS_CNTL & 0x0007;
	if (regs_and_bypass->dcfclk_bypass < 0 || regs_and_bypass->dcfclk_bypass > 4)
		regs_and_bypass->dcfclk_bypass = 0;
	regs_and_bypass->dispclk_bypass = internal.CLK1_CLK0_BYPASS_CNTL & 0x0007;
	if (regs_and_bypass->dispclk_bypass < 0 || regs_and_bypass->dispclk_bypass > 4)
		regs_and_bypass->dispclk_bypass = 0;
	regs_and_bypass->dprefclk_bypass = internal.CLK1_CLK2_BYPASS_CNTL & 0x0007;
	if (regs_and_bypass->dprefclk_bypass < 0 || regs_and_bypass->dprefclk_bypass > 4)
		regs_and_bypass->dprefclk_bypass = 0;

	if (log_info->enabled) {
		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "clk_type,clk_value,deepsleep_cntl,deepsleep_allow,bypass\n");
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "dcfclk,%d,%d,%d,%s\n",
			regs_and_bypass->dcfclk,
			regs_and_bypass->dcf_deep_sleep_divider,
			regs_and_bypass->dcf_deep_sleep_allow,
			bypass_clks[(int) regs_and_bypass->dcfclk_bypass]);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "dprefclk,%d,N/A,N/A,%s\n",
			regs_and_bypass->dprefclk,
			bypass_clks[(int) regs_and_bypass->dprefclk_bypass]);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "dispclk,%d,N/A,N/A,%s\n",
			regs_and_bypass->dispclk,
			bypass_clks[(int) regs_and_bypass->dispclk_bypass]);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		//split
		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "SPLIT\n");
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		// REGISTER VALUES
		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "reg_name,value,clk_type\n");
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK3_CURRENT_CNT,%d,dcfclk\n",
				internal.CLK1_CLK3_CURRENT_CNT);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK3_DS_CNTL,%d,dcf_deep_sleep_divider\n",
					internal.CLK1_CLK3_DS_CNTL);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK3_ALLOW_DS,%d,dcf_deep_sleep_allow\n",
					internal.CLK1_CLK3_ALLOW_DS);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK2_CURRENT_CNT,%d,dprefclk\n",
					internal.CLK1_CLK2_CURRENT_CNT);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK0_CURRENT_CNT,%d,dispclk\n",
					internal.CLK1_CLK0_CURRENT_CNT);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK1_CURRENT_CNT,%d,dppclk\n",
					internal.CLK1_CLK1_CURRENT_CNT);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK3_BYPASS_CNTL,%d,dcfclk_bypass\n",
					internal.CLK1_CLK3_BYPASS_CNTL);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK2_BYPASS_CNTL,%d,dprefclk_bypass\n",
					internal.CLK1_CLK2_BYPASS_CNTL);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK0_BYPASS_CNTL,%d,dispclk_bypass\n",
					internal.CLK1_CLK0_BYPASS_CNTL);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;

		chars_printed = snprintf_count(log_info->pBuf, remaining_buffer, "CLK1_CLK1_BYPASS_CNTL,%d,dppclk_bypass\n",
					internal.CLK1_CLK1_BYPASS_CNTL);
		remaining_buffer -= chars_printed;
		*log_info->sum_chars_printed += chars_printed;
		log_info->pBuf += chars_printed;
	}
}