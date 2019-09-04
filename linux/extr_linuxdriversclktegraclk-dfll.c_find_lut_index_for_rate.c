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
struct tegra_dfll {int i2c_lut_size; int /*<<< orphan*/ * i2c_lut; int /*<<< orphan*/  vdd_reg; TYPE_1__* soc; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (int /*<<< orphan*/ ,unsigned long*) ; 
 int dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int regulator_list_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_lut_index_for_rate(struct tegra_dfll *td, unsigned long rate)
{
	struct dev_pm_opp *opp;
	int i, uv;

	opp = dev_pm_opp_find_freq_ceil(td->soc->dev, &rate);
	if (IS_ERR(opp))
		return PTR_ERR(opp);

	uv = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	for (i = 0; i < td->i2c_lut_size; i++) {
		if (regulator_list_voltage(td->vdd_reg, td->i2c_lut[i]) == uv)
			return i;
	}

	return -ENOENT;
}