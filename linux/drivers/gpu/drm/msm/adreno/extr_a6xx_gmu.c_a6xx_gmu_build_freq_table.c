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
typedef  int u32 ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 scalar_t__ WARN (int,char*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (struct device*,unsigned long*) ; 
 int dev_pm_opp_get_opp_count (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 

__attribute__((used)) static int a6xx_gmu_build_freq_table(struct device *dev, unsigned long *freqs,
		u32 size)
{
	int count = dev_pm_opp_get_opp_count(dev);
	struct dev_pm_opp *opp;
	int i, index = 0;
	unsigned long freq = 1;

	/*
	 * The OPP table doesn't contain the "off" frequency level so we need to
	 * add 1 to the table size to account for it
	 */

	if (WARN(count + 1 > size,
		"The GMU frequency table is being truncated\n"))
		count = size - 1;

	/* Set the "off" frequency */
	freqs[index++] = 0;

	for (i = 0; i < count; i++) {
		opp = dev_pm_opp_find_freq_ceil(dev, &freq);
		if (IS_ERR(opp))
			break;

		dev_pm_opp_put(opp);
		freqs[index++] = freq++;
	}

	return index;
}