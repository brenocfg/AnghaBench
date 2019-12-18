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
struct regmap_config {int reg_bits; int val_bits; } ;
struct regmap {int dummy; } ;
struct i3c_device_id {scalar_t__ data; } ;
struct i3c_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i3c (struct i3c_device*,struct regmap_config*) ; 
 struct i3c_device_id* i3c_device_match_id (struct i3c_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_lsm6dsx_i3c_ids ; 
 int st_lsm6dsx_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t,struct regmap*) ; 

__attribute__((used)) static int st_lsm6dsx_i3c_probe(struct i3c_device *i3cdev)
{
	struct regmap_config st_lsm6dsx_i3c_regmap_config = {
		.reg_bits = 8,
		.val_bits = 8,
	};
	const struct i3c_device_id *id = i3c_device_match_id(i3cdev,
							    st_lsm6dsx_i3c_ids);
	struct regmap *regmap;

	regmap = devm_regmap_init_i3c(i3cdev, &st_lsm6dsx_i3c_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&i3cdev->dev, "Failed to register i3c regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return st_lsm6dsx_probe(&i3cdev->dev, 0, (uintptr_t)id->data, regmap);
}