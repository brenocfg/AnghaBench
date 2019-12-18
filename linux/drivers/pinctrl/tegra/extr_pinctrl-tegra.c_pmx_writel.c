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
typedef  size_t u32 ;
struct tegra_pmx {size_t* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmx_readl (struct tegra_pmx*,size_t,size_t) ; 
 int /*<<< orphan*/  writel_relaxed (size_t,size_t) ; 

__attribute__((used)) static inline void pmx_writel(struct tegra_pmx *pmx, u32 val, u32 bank, u32 reg)
{
	writel_relaxed(val, pmx->regs[bank] + reg);
	/* make sure pinmux register write completed */
	pmx_readl(pmx, bank, reg);
}