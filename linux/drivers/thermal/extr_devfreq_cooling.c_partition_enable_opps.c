#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct devfreq_cooling_device {int freq_table_size; unsigned int* freq_table; TYPE_2__* devfreq; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int dev_pm_opp_disable (struct device*,unsigned int) ; 
 int dev_pm_opp_enable (struct device*,unsigned int) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_exact (struct device*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 

__attribute__((used)) static int partition_enable_opps(struct devfreq_cooling_device *dfc,
				 unsigned long cdev_state)
{
	int i;
	struct device *dev = dfc->devfreq->dev.parent;

	for (i = 0; i < dfc->freq_table_size; i++) {
		struct dev_pm_opp *opp;
		int ret = 0;
		unsigned int freq = dfc->freq_table[i];
		bool want_enable = i >= cdev_state ? true : false;

		opp = dev_pm_opp_find_freq_exact(dev, freq, !want_enable);

		if (PTR_ERR(opp) == -ERANGE)
			continue;
		else if (IS_ERR(opp))
			return PTR_ERR(opp);

		dev_pm_opp_put(opp);

		if (want_enable)
			ret = dev_pm_opp_enable(dev, freq);
		else
			ret = dev_pm_opp_disable(dev, freq);

		if (ret)
			return ret;
	}

	return 0;
}