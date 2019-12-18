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
struct dwc3_qcom {int is_suspended; int num_clocks; int /*<<< orphan*/  qscratch_base; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWR_EVNT_IRQ_STAT_REG ; 
 int PWR_EVNT_LPM_IN_L2_MASK ; 
 int PWR_EVNT_LPM_OUT_L2_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_qcom_disable_interrupts (struct dwc3_qcom*) ; 
 int /*<<< orphan*/  dwc3_qcom_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dwc3_qcom_resume(struct dwc3_qcom *qcom)
{
	int ret;
	int i;

	if (!qcom->is_suspended)
		return 0;

	dwc3_qcom_disable_interrupts(qcom);

	for (i = 0; i < qcom->num_clocks; i++) {
		ret = clk_prepare_enable(qcom->clks[i]);
		if (ret < 0) {
			while (--i >= 0)
				clk_disable_unprepare(qcom->clks[i]);
			return ret;
		}
	}

	/* Clear existing events from PHY related to L2 in/out */
	dwc3_qcom_setbits(qcom->qscratch_base, PWR_EVNT_IRQ_STAT_REG,
			  PWR_EVNT_LPM_IN_L2_MASK | PWR_EVNT_LPM_OUT_L2_MASK);

	qcom->is_suspended = false;

	return 0;
}