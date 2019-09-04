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
struct tegra_devfreq_device {int dummy; } ;
struct tegra_devfreq {struct tegra_devfreq_device* devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_DEV_CTRL ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN ; 
 unsigned int ARRAY_SIZE (struct tegra_devfreq_device*) ; 
 int /*<<< orphan*/  actmon_write_barrier (struct tegra_devfreq*) ; 
 int /*<<< orphan*/  device_readl (struct tegra_devfreq_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_writel (struct tegra_devfreq_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_actmon_disable_interrupts(struct tegra_devfreq *tegra)
{
	struct tegra_devfreq_device *dev;
	u32 val;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(tegra->devices); i++) {
		dev = &tegra->devices[i];

		val = device_readl(dev, ACTMON_DEV_CTRL);
		val &= ~ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN;
		val &= ~ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN;
		val &= ~ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
		val &= ~ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;

		device_writel(dev, val, ACTMON_DEV_CTRL);
	}

	actmon_write_barrier(tegra);
}