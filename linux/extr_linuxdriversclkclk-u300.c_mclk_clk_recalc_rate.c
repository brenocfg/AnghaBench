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
typedef  int u16 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST 132 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH 131 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE 130 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW 129 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER 128 
 scalar_t__ U300_SYSCON_MMF0R ; 
 int U300_SYSCON_MMF0R_MASK ; 
 int readw (scalar_t__) ; 
 int syscon_get_perf () ; 
 scalar_t__ syscon_vbase ; 

__attribute__((used)) static unsigned long
mclk_clk_recalc_rate(struct clk_hw *hw,
		     unsigned long parent_rate)
{
	u16 perf = syscon_get_perf();

	switch (perf) {
	case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER:
		/*
		 * Here, the 208 MHz PLL gets shut down and the always
		 * on 13 MHz PLL used for RTC etc kicks into use
		 * instead.
		 */
		return 13000000;
	case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW:
	case U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE:
	case U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH:
	case U300_SYSCON_CCR_CLKING_PERFORMANCE_BEST:
	{
		/*
		 * This clock is under program control. The register is
		 * divided in two nybbles, bit 7-4 gives cycles-1 to count
		 * high, bit 3-0 gives cycles-1 to count low. Distribute
		 * these with no more than 1 cycle difference between
		 * low and high and add low and high to get the actual
		 * divisor. The base PLL is 208 MHz. Writing 0x00 will
		 * divide by 1 and 1 so the highest frequency possible
		 * is 104 MHz.
		 *
		 * e.g. 0x54 =>
		 * f = 208 / ((5+1) + (4+1)) = 208 / 11 = 18.9 MHz
		 */
		u16 val = readw(syscon_vbase + U300_SYSCON_MMF0R) &
			U300_SYSCON_MMF0R_MASK;
		switch (val) {
		case 0x0054:
			return 18900000;
		case 0x0044:
			return 20800000;
		case 0x0043:
			return 23100000;
		case 0x0033:
			return 26000000;
		case 0x0032:
			return 29700000;
		case 0x0022:
			return 34700000;
		case 0x0021:
			return 41600000;
		case 0x0011:
			return 52000000;
		case 0x0000:
			return 104000000;
		default:
			break;
		}
	}
	default:
		break;
	}
	return parent_rate;
}