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
struct clk {int rate; int /*<<< orphan*/  enable_reg; } ;
typedef  int __u16 ;

/* Variables and functions */
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 unsigned int calc_ext_dsor (unsigned long) ; 

int omap1_set_ext_clk_rate(struct clk *clk, unsigned long rate)
{
	unsigned dsor;
	__u16 ratio_bits;

	dsor = calc_ext_dsor(rate);
	clk->rate = 96000000 / dsor;
	if (dsor > 8)
		ratio_bits = ((dsor - 8) / 2 + 6) << 2;
	else
		ratio_bits = (dsor - 2) << 2;

	ratio_bits |= __raw_readw(clk->enable_reg) & ~0xfd;
	__raw_writew(ratio_bits, clk->enable_reg);

	return 0;
}