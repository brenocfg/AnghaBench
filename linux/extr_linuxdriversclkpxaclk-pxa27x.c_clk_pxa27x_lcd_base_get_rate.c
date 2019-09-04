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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCR ; 
 int CCCR_CPDIS_BIT ; 
 int CCCR_LCD_26_BIT ; 
 int /*<<< orphan*/  CCSR ; 
 unsigned long CCSR_L_MASK ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_pxa27x_lcd_base_get_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	unsigned int l, osc_forced;
	unsigned long ccsr = readl(CCSR);
	unsigned long cccr = readl(CCCR);

	l  = ccsr & CCSR_L_MASK;
	osc_forced = ccsr & (1 << CCCR_CPDIS_BIT);
	if (osc_forced) {
		if (cccr & (1 << CCCR_LCD_26_BIT))
			return parent_rate * 2;
		else
			return parent_rate;
	}

	if (l <= 7)
		return parent_rate;
	if (l <= 16)
		return parent_rate / 2;
	return parent_rate / 4;
}