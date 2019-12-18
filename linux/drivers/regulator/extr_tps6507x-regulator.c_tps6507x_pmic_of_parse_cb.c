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
typedef  int /*<<< orphan*/  u32 ;
struct tps_info {int /*<<< orphan*/  defdcdc_default; } ;
struct tps6507x_pmic {struct tps_info** info; } ;
struct regulator_desc {size_t id; } ;
struct regulator_config {struct tps6507x_pmic* driver_data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps6507x_pmic_of_parse_cb(struct device_node *np,
				     const struct regulator_desc *desc,
				     struct regulator_config *config)
{
	struct tps6507x_pmic *tps = config->driver_data;
	struct tps_info *info = tps->info[desc->id];
	u32 prop;
	int ret;

	ret = of_property_read_u32(np, "ti,defdcdc_default", &prop);
	if (!ret)
		info->defdcdc_default = prop;

	return 0;
}