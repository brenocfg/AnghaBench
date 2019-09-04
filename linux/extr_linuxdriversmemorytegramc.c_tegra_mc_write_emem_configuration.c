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
struct tegra_mc_timing {unsigned long rate; int /*<<< orphan*/ * emem_data; } ;
struct tegra_mc {unsigned int num_timings; TYPE_1__* soc; int /*<<< orphan*/  dev; struct tegra_mc_timing* timings; } ;
struct TYPE_2__ {unsigned int num_emem_regs; int /*<<< orphan*/ * emem_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  mc_writel (struct tegra_mc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tegra_mc_write_emem_configuration(struct tegra_mc *mc, unsigned long rate)
{
	unsigned int i;
	struct tegra_mc_timing *timing = NULL;

	for (i = 0; i < mc->num_timings; i++) {
		if (mc->timings[i].rate == rate) {
			timing = &mc->timings[i];
			break;
		}
	}

	if (!timing) {
		dev_err(mc->dev, "no memory timing registered for rate %lu\n",
			rate);
		return;
	}

	for (i = 0; i < mc->soc->num_emem_regs; ++i)
		mc_writel(mc, timing->emem_data[i], mc->soc->emem_regs[i]);
}