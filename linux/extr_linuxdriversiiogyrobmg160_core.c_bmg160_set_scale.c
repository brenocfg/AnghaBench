#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  dps_range; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int scale; int /*<<< orphan*/  dps_range; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BMG160_REG_RANGE ; 
 int EINVAL ; 
 TYPE_1__* bmg160_scale_table ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmg160_set_scale(struct bmg160_data *data, int val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(bmg160_scale_table); ++i) {
		if (bmg160_scale_table[i].scale == val) {
			ret = regmap_write(data->regmap, BMG160_REG_RANGE,
					   bmg160_scale_table[i].dps_range);
			if (ret < 0) {
				dev_err(dev, "Error writing reg_range\n");
				return ret;
			}
			data->dps_range = bmg160_scale_table[i].dps_range;
			return 0;
		}
	}

	return -EINVAL;
}