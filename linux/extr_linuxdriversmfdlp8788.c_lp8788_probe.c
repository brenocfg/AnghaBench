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
struct lp8788_platform_data {int dummy; } ;
struct lp8788 {int /*<<< orphan*/ * dev; struct lp8788_platform_data* pdata; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct lp8788_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct lp8788* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp8788*) ; 
 int /*<<< orphan*/  lp8788_devs ; 
 int lp8788_irq_init (struct lp8788*,int /*<<< orphan*/ ) ; 
 int lp8788_platform_init (struct lp8788*) ; 
 int /*<<< orphan*/  lp8788_regmap_config ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8788_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct lp8788 *lp;
	struct lp8788_platform_data *pdata = dev_get_platdata(&cl->dev);
	int ret;

	lp = devm_kzalloc(&cl->dev, sizeof(struct lp8788), GFP_KERNEL);
	if (!lp)
		return -ENOMEM;

	lp->regmap = devm_regmap_init_i2c(cl, &lp8788_regmap_config);
	if (IS_ERR(lp->regmap)) {
		ret = PTR_ERR(lp->regmap);
		dev_err(&cl->dev, "regmap init i2c err: %d\n", ret);
		return ret;
	}

	lp->pdata = pdata;
	lp->dev = &cl->dev;
	i2c_set_clientdata(cl, lp);

	ret = lp8788_platform_init(lp);
	if (ret)
		return ret;

	ret = lp8788_irq_init(lp, cl->irq);
	if (ret)
		return ret;

	return mfd_add_devices(lp->dev, -1, lp8788_devs,
			       ARRAY_SIZE(lp8788_devs), NULL, 0, NULL);
}