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
struct tegra_xusb_padctl {int dummy; } ;
struct tegra_xusb_lane_soc {int num_funcs; int mask; int shift; int /*<<< orphan*/  offset; } ;
struct tegra_xusb_lane {int function; struct tegra_xusb_lane_soc* soc; TYPE_1__* pad; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_xusb_lane_program(struct tegra_xusb_lane *lane)
{
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	const struct tegra_xusb_lane_soc *soc = lane->soc;
	u32 value;

	/* skip single function lanes */
	if (soc->num_funcs < 2)
		return;

	/* choose function */
	value = padctl_readl(padctl, soc->offset);
	value &= ~(soc->mask << soc->shift);
	value |= lane->function << soc->shift;
	padctl_writel(padctl, value, soc->offset);
}