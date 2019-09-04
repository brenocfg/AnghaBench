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
struct tegra_dfll {int* i2c_lut; int i2c_lut_size; TYPE_2__* soc; int /*<<< orphan*/  dev; int /*<<< orphan*/  dvco_rate_min; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cvb; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int min_millivolts; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int MAX_DFLL_VOLTAGES ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (int /*<<< orphan*/ ,unsigned long*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_floor (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  dev_pm_opp_get_freq (struct dev_pm_opp*) ; 
 int dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int find_vdd_map_entry_exact (struct tegra_dfll*,int) ; 
 int find_vdd_map_entry_min (struct tegra_dfll*,int) ; 
 scalar_t__ max (int,int) ; 

__attribute__((used)) static int dfll_build_i2c_lut(struct tegra_dfll *td)
{
	int ret = -EINVAL;
	int j, v, v_max, v_opp;
	int selector;
	unsigned long rate;
	struct dev_pm_opp *opp;
	int lut;

	rate = ULONG_MAX;
	opp = dev_pm_opp_find_freq_floor(td->soc->dev, &rate);
	if (IS_ERR(opp)) {
		dev_err(td->dev, "couldn't get vmax opp, empty opp table?\n");
		goto out;
	}
	v_max = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	v = td->soc->cvb->min_millivolts * 1000;
	lut = find_vdd_map_entry_exact(td, v);
	if (lut < 0)
		goto out;
	td->i2c_lut[0] = lut;

	for (j = 1, rate = 0; ; rate++) {
		opp = dev_pm_opp_find_freq_ceil(td->soc->dev, &rate);
		if (IS_ERR(opp))
			break;
		v_opp = dev_pm_opp_get_voltage(opp);

		if (v_opp <= td->soc->cvb->min_millivolts * 1000)
			td->dvco_rate_min = dev_pm_opp_get_freq(opp);

		dev_pm_opp_put(opp);

		for (;;) {
			v += max(1, (v_max - v) / (MAX_DFLL_VOLTAGES - j));
			if (v >= v_opp)
				break;

			selector = find_vdd_map_entry_min(td, v);
			if (selector < 0)
				goto out;
			if (selector != td->i2c_lut[j - 1])
				td->i2c_lut[j++] = selector;
		}

		v = (j == MAX_DFLL_VOLTAGES - 1) ? v_max : v_opp;
		selector = find_vdd_map_entry_exact(td, v);
		if (selector < 0)
			goto out;
		if (selector != td->i2c_lut[j - 1])
			td->i2c_lut[j++] = selector;

		if (v >= v_max)
			break;
	}
	td->i2c_lut_size = j;

	if (!td->dvco_rate_min)
		dev_err(td->dev, "no opp above DFLL minimum voltage %d mV\n",
			td->soc->cvb->min_millivolts);
	else
		ret = 0;

out:
	return ret;
}