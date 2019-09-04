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
struct clk {scalar_t__* rates; scalar_t__ rate; int module; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifccr ; 
 unsigned int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_cgu_w32 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clkout_enable(struct clk *clk)
{
	int i;

	/* get the correct rate */
	for (i = 0; i < 4; i++) {
		if (clk->rates[i] == clk->rate) {
			int shift = 14 - (2 * clk->module);
			int enable = 7 - clk->module;
			unsigned int val = ltq_cgu_r32(ifccr);

			val &= ~(3 << shift);
			val |= i << shift;
			val |= enable;
			ltq_cgu_w32(val, ifccr);
			return 0;
		}
	}
	return -1;
}