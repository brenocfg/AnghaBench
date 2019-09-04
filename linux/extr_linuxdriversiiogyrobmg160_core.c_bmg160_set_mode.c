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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMG160_REG_PMU_LPW ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmg160_set_mode(struct bmg160_data *data, u8 mode)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	ret = regmap_write(data->regmap, BMG160_REG_PMU_LPW, mode);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_pmu_lpw\n");
		return ret;
	}

	return 0;
}