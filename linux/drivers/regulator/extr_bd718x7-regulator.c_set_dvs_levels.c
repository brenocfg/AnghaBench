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
struct regulator_desc {int n_voltages; int /*<<< orphan*/  vsel_mask; } ;
struct regmap {int dummy; } ;
struct of_dvs_setting {int /*<<< orphan*/  reg; int /*<<< orphan*/  prop; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVS_BUCK_RUN_MASK ; 
 int EINVAL ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regulator_desc_list_voltage_linear_range (struct regulator_desc const*,int) ; 

__attribute__((used)) static int set_dvs_levels(const struct of_dvs_setting *dvs,
			  struct device_node *np,
			  const struct regulator_desc *desc,
			  struct regmap *regmap)
{
	int ret, i;
	unsigned int uv;

	ret = of_property_read_u32(np, dvs->prop, &uv);
	if (ret) {
		if (ret != -EINVAL)
			return ret;
		return 0;
	}

	for (i = 0; i < desc->n_voltages; i++) {
		ret = regulator_desc_list_voltage_linear_range(desc, i);
		if (ret < 0)
			continue;
		if (ret == uv) {
			i <<= ffs(desc->vsel_mask) - 1;
			ret = regmap_update_bits(regmap, dvs->reg,
						 DVS_BUCK_RUN_MASK, i);
			break;
		}
	}
	return ret;
}