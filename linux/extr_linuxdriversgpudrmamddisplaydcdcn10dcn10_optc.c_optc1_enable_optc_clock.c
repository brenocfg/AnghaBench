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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OPTC_INPUT_CLK_EN ; 
 int /*<<< orphan*/  OPTC_INPUT_CLK_GATE_DIS ; 
 int /*<<< orphan*/  OPTC_INPUT_CLK_ON ; 
 int /*<<< orphan*/  OPTC_INPUT_CLOCK_CONTROL ; 
 int /*<<< orphan*/  OTG_CLOCK_CONTROL ; 
 int /*<<< orphan*/  OTG_CLOCK_EN ; 
 int /*<<< orphan*/  OTG_CLOCK_GATE_DIS ; 
 int /*<<< orphan*/  OTG_CLOCK_ON ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

void optc1_enable_optc_clock(struct timing_generator *optc, bool enable)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	if (enable) {
		REG_UPDATE_2(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_EN, 1,
				OPTC_INPUT_CLK_GATE_DIS, 1);

		REG_WAIT(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_ON, 1,
				1, 1000);

		/* Enable clock */
		REG_UPDATE_2(OTG_CLOCK_CONTROL,
				OTG_CLOCK_EN, 1,
				OTG_CLOCK_GATE_DIS, 1);
		REG_WAIT(OTG_CLOCK_CONTROL,
				OTG_CLOCK_ON, 1,
				1, 1000);
	} else  {
		REG_UPDATE_2(OTG_CLOCK_CONTROL,
				OTG_CLOCK_GATE_DIS, 0,
				OTG_CLOCK_EN, 0);

		REG_UPDATE_2(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_GATE_DIS, 0,
				OPTC_INPUT_CLK_EN, 0);
	}
}