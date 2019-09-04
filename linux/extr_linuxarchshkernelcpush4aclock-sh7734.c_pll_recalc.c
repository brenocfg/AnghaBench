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
typedef  int u32 ;
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODEMR ; 
 int MODEMR_533MHZ ; 
 int MODEMR_MASK ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pll_recalc(struct clk *clk)
{
	int mode = 12;
	u32 r = __raw_readl(MODEMR);

	if ((r & MODEMR_MASK) & MODEMR_533MHZ)
		mode = 16;

	return clk->parent->rate * mode;
}