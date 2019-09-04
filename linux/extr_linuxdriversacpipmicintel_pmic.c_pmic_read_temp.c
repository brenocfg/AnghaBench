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
typedef  int u64 ;
struct intel_pmic_opregion {int /*<<< orphan*/  lpat_table; int /*<<< orphan*/  regmap; TYPE_1__* data; } ;
struct TYPE_2__ {int (* get_raw_temp ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int acpi_lpat_raw_to_temp (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pmic_read_temp(struct intel_pmic_opregion *opregion,
			  int reg, u64 *value)
{
	int raw_temp, temp;

	if (!opregion->data->get_raw_temp)
		return -ENXIO;

	raw_temp = opregion->data->get_raw_temp(opregion->regmap, reg);
	if (raw_temp < 0)
		return raw_temp;

	if (!opregion->lpat_table) {
		*value = raw_temp;
		return 0;
	}

	temp = acpi_lpat_raw_to_temp(opregion->lpat_table, raw_temp);
	if (temp < 0)
		return temp;

	*value = temp;
	return 0;
}