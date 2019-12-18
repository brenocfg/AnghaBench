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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct apds9960_data {void* reg_enable_pxs; void* reg_enable_ges; void* reg_enable_als; void* reg_int_pxs; void* reg_int_ges; void* reg_int_als; struct regmap* regmap; TYPE_1__* client; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  apds9960_reg_field_enable_als ; 
 int /*<<< orphan*/  apds9960_reg_field_enable_ges ; 
 int /*<<< orphan*/  apds9960_reg_field_enable_pxs ; 
 int /*<<< orphan*/  apds9960_reg_field_int_als ; 
 int /*<<< orphan*/  apds9960_reg_field_int_ges ; 
 int /*<<< orphan*/  apds9960_reg_field_int_pxs ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_regmap_field_alloc (struct device*,struct regmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apds9960_regfield_init(struct apds9960_data *data)
{
	struct device *dev = &data->client->dev;
	struct regmap *regmap = data->regmap;

	data->reg_int_als = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_int_als);
	if (IS_ERR(data->reg_int_als)) {
		dev_err(dev, "INT ALS reg field init failed\n");
		return PTR_ERR(data->reg_int_als);
	}

	data->reg_int_ges = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_int_ges);
	if (IS_ERR(data->reg_int_ges)) {
		dev_err(dev, "INT gesture reg field init failed\n");
		return PTR_ERR(data->reg_int_ges);
	}

	data->reg_int_pxs = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_int_pxs);
	if (IS_ERR(data->reg_int_pxs)) {
		dev_err(dev, "INT pxs reg field init failed\n");
		return PTR_ERR(data->reg_int_pxs);
	}

	data->reg_enable_als = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_als);
	if (IS_ERR(data->reg_enable_als)) {
		dev_err(dev, "Enable ALS reg field init failed\n");
		return PTR_ERR(data->reg_enable_als);
	}

	data->reg_enable_ges = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_ges);
	if (IS_ERR(data->reg_enable_ges)) {
		dev_err(dev, "Enable gesture reg field init failed\n");
		return PTR_ERR(data->reg_enable_ges);
	}

	data->reg_enable_pxs = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_pxs);
	if (IS_ERR(data->reg_enable_pxs)) {
		dev_err(dev, "Enable PXS reg field init failed\n");
		return PTR_ERR(data->reg_enable_pxs);
	}

	return 0;
}