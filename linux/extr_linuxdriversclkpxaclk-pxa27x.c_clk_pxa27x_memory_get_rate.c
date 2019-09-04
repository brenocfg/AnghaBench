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
 int CCCR_A_BIT ; 
 int CCCR_CPDIS_BIT ; 
 int /*<<< orphan*/  CCSR ; 
 unsigned long CCSR_L_MASK ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_pxa27x_memory_get_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	unsigned int a, l, osc_forced;
	unsigned long cccr = readl(CCCR);
	unsigned long ccsr = readl(CCSR);

	osc_forced = ccsr & (1 << CCCR_CPDIS_BIT);
	a = cccr & (1 << CCCR_A_BIT);
	l  = ccsr & CCSR_L_MASK;

	if (osc_forced || a)
		return parent_rate;
	if (l <= 10)
		return parent_rate;
	if (l <= 20)
		return parent_rate / 2;
	return parent_rate / 4;
}