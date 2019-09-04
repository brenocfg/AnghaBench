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
typedef  unsigned int u32 ;
struct tegra_nand_controller {scalar_t__ regs; int /*<<< orphan*/  clk; } ;
struct nand_sdr_timings {int tCS_min; int tCH_min; int tALS_min; int tALH_min; int tRP_min; int tREA_max; int tWB_max; int tWHR_min; int tWH_min; int tWP_min; int tREH_min; int tADL_min; int /*<<< orphan*/  tRC_min; int /*<<< orphan*/  tRR_min; int /*<<< orphan*/  tAR_min; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 int /*<<< orphan*/  OFFSET (unsigned int,int) ; 
 scalar_t__ TIMING_1 ; 
 scalar_t__ TIMING_2 ; 
 unsigned int TIMING_TADL (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TCR_TAR_TRR (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TCS (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TRH (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TRP (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TRP_RESP (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TWB (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TWH (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TWHR (int /*<<< orphan*/ ) ; 
 unsigned int TIMING_TWP (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int max3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void tegra_nand_setup_timing(struct tegra_nand_controller *ctrl,
				    const struct nand_sdr_timings *timings)
{
	/*
	 * The period (and all other timings in this function) is in ps,
	 * so need to take care here to avoid integer overflows.
	 */
	unsigned int rate = clk_get_rate(ctrl->clk) / 1000000;
	unsigned int period = DIV_ROUND_UP(1000000, rate);
	u32 val, reg = 0;

	val = DIV_ROUND_UP(max3(timings->tAR_min, timings->tRR_min,
				timings->tRC_min), period);
	reg |= TIMING_TCR_TAR_TRR(OFFSET(val, 3));

	val = DIV_ROUND_UP(max(max(timings->tCS_min, timings->tCH_min),
			       max(timings->tALS_min, timings->tALH_min)),
			   period);
	reg |= TIMING_TCS(OFFSET(val, 2));

	val = DIV_ROUND_UP(max(timings->tRP_min, timings->tREA_max) + 6000,
			   period);
	reg |= TIMING_TRP(OFFSET(val, 1)) | TIMING_TRP_RESP(OFFSET(val, 1));

	reg |= TIMING_TWB(OFFSET(DIV_ROUND_UP(timings->tWB_max, period), 1));
	reg |= TIMING_TWHR(OFFSET(DIV_ROUND_UP(timings->tWHR_min, period), 1));
	reg |= TIMING_TWH(OFFSET(DIV_ROUND_UP(timings->tWH_min, period), 1));
	reg |= TIMING_TWP(OFFSET(DIV_ROUND_UP(timings->tWP_min, period), 1));
	reg |= TIMING_TRH(OFFSET(DIV_ROUND_UP(timings->tREH_min, period), 1));

	writel_relaxed(reg, ctrl->regs + TIMING_1);

	val = DIV_ROUND_UP(timings->tADL_min, period);
	reg = TIMING_TADL(OFFSET(val, 3));

	writel_relaxed(reg, ctrl->regs + TIMING_2);
}