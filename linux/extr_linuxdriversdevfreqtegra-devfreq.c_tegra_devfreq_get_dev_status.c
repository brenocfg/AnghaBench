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
struct tegra_devfreq_device {int dummy; } ;
struct tegra_devfreq {int cur_freq; struct tegra_devfreq_device* devices; } ;
struct device {int dummy; } ;
struct devfreq_dev_status {int current_frequency; int busy_time; int total_time; struct tegra_devfreq* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_DEV_AVG_COUNT ; 
 int ACTMON_SAMPLING_PERIOD ; 
 int BUS_SATURATION_RATIO ; 
 size_t MCALL ; 
 struct tegra_devfreq* dev_get_drvdata (struct device*) ; 
 int device_readl (struct tegra_devfreq_device*,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static int tegra_devfreq_get_dev_status(struct device *dev,
					struct devfreq_dev_status *stat)
{
	struct tegra_devfreq *tegra = dev_get_drvdata(dev);
	struct tegra_devfreq_device *actmon_dev;

	stat->current_frequency = tegra->cur_freq;

	/* To be used by the tegra governor */
	stat->private_data = tegra;

	/* The below are to be used by the other governors */

	actmon_dev = &tegra->devices[MCALL];

	/* Number of cycles spent on memory access */
	stat->busy_time = device_readl(actmon_dev, ACTMON_DEV_AVG_COUNT);

	/* The bus can be considered to be saturated way before 100% */
	stat->busy_time *= 100 / BUS_SATURATION_RATIO;

	/* Number of cycles in a sampling period */
	stat->total_time = ACTMON_SAMPLING_PERIOD * tegra->cur_freq;

	stat->busy_time = min(stat->busy_time, stat->total_time);

	return 0;
}