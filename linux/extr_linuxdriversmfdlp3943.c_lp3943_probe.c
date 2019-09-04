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
struct lp3943 {int /*<<< orphan*/  mux_cfg; struct device* dev; int /*<<< orphan*/  pdata; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 struct lp3943* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp3943*) ; 
 int /*<<< orphan*/  lp3943_devs ; 
 int /*<<< orphan*/  lp3943_mux_cfg ; 
 int /*<<< orphan*/  lp3943_regmap_config ; 

__attribute__((used)) static int lp3943_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct lp3943 *lp3943;
	struct device *dev = &cl->dev;

	lp3943 = devm_kzalloc(dev, sizeof(*lp3943), GFP_KERNEL);
	if (!lp3943)
		return -ENOMEM;

	lp3943->regmap = devm_regmap_init_i2c(cl, &lp3943_regmap_config);
	if (IS_ERR(lp3943->regmap))
		return PTR_ERR(lp3943->regmap);

	lp3943->pdata = dev_get_platdata(dev);
	lp3943->dev = dev;
	lp3943->mux_cfg = lp3943_mux_cfg;
	i2c_set_clientdata(cl, lp3943);

	return devm_mfd_add_devices(dev, -1, lp3943_devs,
				    ARRAY_SIZE(lp3943_devs),
				    NULL, 0, NULL);
}