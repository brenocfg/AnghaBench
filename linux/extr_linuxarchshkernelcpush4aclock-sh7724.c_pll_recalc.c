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
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCRA ; 
 int /*<<< orphan*/  PLLCR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pll_recalc(struct clk *clk)
{
	unsigned long mult = 1;

	if (__raw_readl(PLLCR) & 0x4000)
		mult = (((__raw_readl(FRQCRA) >> 24) & 0x3f) + 1) * 2;

	return clk->parent->rate * mult;
}