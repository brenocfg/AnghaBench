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
struct tegra_dfll {int /*<<< orphan*/  dev; int /*<<< orphan*/  vdd_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_count_voltages (int /*<<< orphan*/ ) ; 
 int regulator_list_voltage (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_vdd_map_entry_exact(struct tegra_dfll *td, int uV)
{
	int i, n_voltages, reg_uV;

	n_voltages = regulator_count_voltages(td->vdd_reg);
	for (i = 0; i < n_voltages; i++) {
		reg_uV = regulator_list_voltage(td->vdd_reg, i);
		if (reg_uV < 0)
			break;

		if (uV == reg_uV)
			return i;
	}

	dev_err(td->dev, "no voltage map entry for %d uV\n", uV);
	return -EINVAL;
}