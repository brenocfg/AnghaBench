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
struct clk {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQCR ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int* pll1rate ; 
 int pll2_mult ; 

__attribute__((used)) static void master_clk_init(struct clk *clk)
{
	clk->rate *= pll2_mult * pll1rate[(__raw_readw(FREQCR) >> 8) & 7];
}