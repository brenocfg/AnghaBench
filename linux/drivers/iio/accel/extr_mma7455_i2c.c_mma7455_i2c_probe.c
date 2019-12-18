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
struct i2c_device_id {char* name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int mma7455_core_probe (int /*<<< orphan*/ *,struct regmap*,char const*) ; 
 int /*<<< orphan*/  mma7455_core_regmap ; 

__attribute__((used)) static int mma7455_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;
	const char *name = NULL;

	regmap = devm_regmap_init_i2c(i2c, &mma7455_core_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	if (id)
		name = id->name;

	return mma7455_core_probe(&i2c->dev, regmap, name);
}