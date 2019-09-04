#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  stable_bit; int /*<<< orphan*/  enable_bit; } ;
struct TYPE_5__ {TYPE_1__ pll; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CGU_REG_CLKGR ; 
 scalar_t__ CGU_REG_CPPCR ; 
 size_t JZ4740_CLK_PLL ; 
 int JZ_CLOCK_GATE_DMAC ; 
 int JZ_CLOCK_GATE_TCU ; 
 int JZ_CLOCK_GATE_UART0 ; 
 TYPE_3__* cgu ; 
 TYPE_2__* jz4740_cgu_clocks ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void jz4740_clock_resume(void)
{
	uint32_t clkgr, cppcr, stable;

	cppcr = readl(cgu->base + CGU_REG_CPPCR);
	cppcr |= BIT(jz4740_cgu_clocks[JZ4740_CLK_PLL].pll.enable_bit);
	writel(cppcr, cgu->base + CGU_REG_CPPCR);

	stable = BIT(jz4740_cgu_clocks[JZ4740_CLK_PLL].pll.stable_bit);
	do {
		cppcr = readl(cgu->base + CGU_REG_CPPCR);
	} while (!(cppcr & stable));

	clkgr = readl(cgu->base + CGU_REG_CLKGR);
	clkgr &= ~JZ_CLOCK_GATE_TCU;
	clkgr &= ~JZ_CLOCK_GATE_DMAC;
	clkgr &= ~JZ_CLOCK_GATE_UART0;
	writel(clkgr, cgu->base + CGU_REG_CLKGR);
}