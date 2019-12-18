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
typedef  unsigned long u32 ;
struct device {int dummy; } ;
struct devfreq_cooling_device {unsigned long* power_table; unsigned long* freq_table; int freq_table_size; TYPE_2__* power_ops; struct devfreq* devfreq; } ;
struct TYPE_3__ {struct device* parent; } ;
struct devfreq {TYPE_1__ dev; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_4__ {scalar_t__ get_real_power; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_floor (struct device*,unsigned long*) ; 
 int dev_pm_opp_get_opp_count (struct device*) ; 
 int dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 unsigned long get_dynamic_power (struct devfreq_cooling_device*,unsigned long,unsigned long) ; 
 unsigned long get_total_power (struct devfreq_cooling_device*,unsigned long,unsigned long) ; 
 unsigned long* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 

__attribute__((used)) static int devfreq_cooling_gen_tables(struct devfreq_cooling_device *dfc)
{
	struct devfreq *df = dfc->devfreq;
	struct device *dev = df->dev.parent;
	int ret, num_opps;
	unsigned long freq;
	u32 *power_table = NULL;
	u32 *freq_table;
	int i;

	num_opps = dev_pm_opp_get_opp_count(dev);

	if (dfc->power_ops) {
		power_table = kcalloc(num_opps, sizeof(*power_table),
				      GFP_KERNEL);
		if (!power_table)
			return -ENOMEM;
	}

	freq_table = kcalloc(num_opps, sizeof(*freq_table),
			     GFP_KERNEL);
	if (!freq_table) {
		ret = -ENOMEM;
		goto free_power_table;
	}

	for (i = 0, freq = ULONG_MAX; i < num_opps; i++, freq--) {
		unsigned long power, voltage;
		struct dev_pm_opp *opp;

		opp = dev_pm_opp_find_freq_floor(dev, &freq);
		if (IS_ERR(opp)) {
			ret = PTR_ERR(opp);
			goto free_tables;
		}

		voltage = dev_pm_opp_get_voltage(opp) / 1000; /* mV */
		dev_pm_opp_put(opp);

		if (dfc->power_ops) {
			if (dfc->power_ops->get_real_power)
				power = get_total_power(dfc, freq, voltage);
			else
				power = get_dynamic_power(dfc, freq, voltage);

			dev_dbg(dev, "Power table: %lu MHz @ %lu mV: %lu = %lu mW\n",
				freq / 1000000, voltage, power, power);

			power_table[i] = power;
		}

		freq_table[i] = freq;
	}

	if (dfc->power_ops)
		dfc->power_table = power_table;

	dfc->freq_table = freq_table;
	dfc->freq_table_size = num_opps;

	return 0;

free_tables:
	kfree(freq_table);
free_power_table:
	kfree(power_table);

	return ret;
}