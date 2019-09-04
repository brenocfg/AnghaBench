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
typedef  unsigned long u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tcr; int /*<<< orphan*/  cntlo; int /*<<< orphan*/  prdlo; } ;

/* Variables and functions */
 unsigned long TCR_ENAMODELO_MASK ; 
 unsigned long soc_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_writel (unsigned long,int /*<<< orphan*/ *) ; 
 TYPE_1__* timer ; 
 unsigned long timer64_mode ; 

__attribute__((used)) static void timer64_config(unsigned long period)
{
	u32 tcr = soc_readl(&timer->tcr) & ~TCR_ENAMODELO_MASK;

	soc_writel(tcr, &timer->tcr);
	soc_writel(period - 1, &timer->prdlo);
	soc_writel(0, &timer->cntlo);
	tcr |= timer64_mode;
	soc_writel(tcr, &timer->tcr);
}