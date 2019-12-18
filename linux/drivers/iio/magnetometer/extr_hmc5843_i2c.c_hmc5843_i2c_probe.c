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
struct regmap {int dummy; } ;
struct i2c_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int hmc5843_common_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmc5843_i2c_regmap_config ; 

__attribute__((used)) static int hmc5843_i2c_probe(struct i2c_client *cli,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap = devm_regmap_init_i2c(cli,
			&hmc5843_i2c_regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return hmc5843_common_probe(&cli->dev,
			regmap,
			id->driver_data, id->name);
}