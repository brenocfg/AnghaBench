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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_mc {scalar_t__ regs; scalar_t__ regs2; } ;

/* Variables and functions */
 void writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void mc_writel(struct tegra_mc *mc, u32 value,
			     unsigned long offset)
{
	if (mc->regs2 && offset >= 0x24)
		return writel(value, mc->regs2 + offset - 0x3c);

	writel(value, mc->regs + offset);
}