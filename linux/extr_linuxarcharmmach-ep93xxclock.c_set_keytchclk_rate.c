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
struct clk {int enable_mask; unsigned long rate; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long EP93XX_KEYTCHCLK_DIV16 ; 
 unsigned long EP93XX_KEYTCHCLK_DIV4 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_syscon_swlocked_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_keytchclk_rate(struct clk *clk, unsigned long rate)
{
	u32 val;
	u32 div_bit;

	val = __raw_readl(clk->enable_reg);

	/*
	 * The Key Matrix and ADC clocks are configured using the same
	 * System Controller register.  The clock used will be either
	 * 1/4 or 1/16 the external clock rate depending on the
	 * EP93XX_SYSCON_KEYTCHCLKDIV_KDIV/EP93XX_SYSCON_KEYTCHCLKDIV_ADIV
	 * bit being set or cleared.
	 */
	div_bit = clk->enable_mask >> 15;

	if (rate == EP93XX_KEYTCHCLK_DIV4)
		val |= div_bit;
	else if (rate == EP93XX_KEYTCHCLK_DIV16)
		val &= ~div_bit;
	else
		return -EINVAL;

	ep93xx_syscon_swlocked_write(val, clk->enable_reg);
	clk->rate = rate;
	return 0;
}