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
struct tegra_devfreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_GLB_STATUS ; 
 int /*<<< orphan*/  actmon_readl (struct tegra_devfreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void actmon_write_barrier(struct tegra_devfreq *tegra)
{
	/* ensure the update has reached the ACTMON */
	wmb();
	actmon_readl(tegra, ACTMON_GLB_STATUS);
}