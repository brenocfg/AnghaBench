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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_RAW ; 
 int /*<<< orphan*/  PRCMU_HDMICLK ; 
 int /*<<< orphan*/  PRCM_PLLDSI_FREQ ; 
 int clock_divider (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clock_rate (int /*<<< orphan*/ ) ; 
 unsigned long pll_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long round_dsiclk_rate(unsigned long rate)
{
	u32 div;
	unsigned long src_rate;
	long rounded_rate;

	src_rate = pll_rate(PRCM_PLLDSI_FREQ, clock_rate(PRCMU_HDMICLK),
		PLL_RAW);
	div = clock_divider(src_rate, rate);
	rounded_rate = (src_rate / ((div > 2) ? 4 : div));

	return rounded_rate;
}