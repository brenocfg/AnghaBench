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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct regmap {int dummy; } ;
struct intel_pmic_opregion_data {int (* get_policy ) (struct regmap*,int,int,int*) ;int (* update_policy ) (struct regmap*,int,int,int) ;} ;
struct intel_pmic_opregion {struct regmap* regmap; struct intel_pmic_opregion_data* data; } ;

/* Variables and functions */
 scalar_t__ ACPI_READ ; 
 int EINVAL ; 
 int ENXIO ; 
 int stub1 (struct regmap*,int,int,int*) ; 
 int stub2 (struct regmap*,int,int,int) ; 

__attribute__((used)) static int pmic_thermal_pen(struct intel_pmic_opregion *opregion, int reg,
			    int bit, u32 function, u64 *value)
{
	struct intel_pmic_opregion_data *d = opregion->data;
	struct regmap *regmap = opregion->regmap;

	if (!d->get_policy || !d->update_policy)
		return -ENXIO;

	if (function == ACPI_READ)
		return d->get_policy(regmap, reg, bit, value);

	if (*value != 0 && *value != 1)
		return -EINVAL;

	return d->update_policy(regmap, reg, bit, *value);
}