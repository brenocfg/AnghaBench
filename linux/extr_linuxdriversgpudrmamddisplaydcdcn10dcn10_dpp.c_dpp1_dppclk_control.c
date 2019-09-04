#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dpp {int dummy; } ;
struct dcn10_dpp {TYPE_1__* tf_mask; } ;
struct TYPE_2__ {scalar_t__ DPPCLK_RATE_CONTROL; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPPCLK_RATE_CONTROL ; 
 int /*<<< orphan*/  DPP_CLOCK_ENABLE ; 
 int /*<<< orphan*/  DPP_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_dppclk_control(
		struct dpp *dpp_base,
		bool dppclk_div,
		bool enable)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (enable) {
		if (dpp->tf_mask->DPPCLK_RATE_CONTROL)
			REG_UPDATE_2(DPP_CONTROL,
				DPPCLK_RATE_CONTROL, dppclk_div,
				DPP_CLOCK_ENABLE, 1);
		else
			REG_UPDATE(DPP_CONTROL, DPP_CLOCK_ENABLE, 1);
	} else
		REG_UPDATE(DPP_CONTROL, DPP_CLOCK_ENABLE, 0);
}