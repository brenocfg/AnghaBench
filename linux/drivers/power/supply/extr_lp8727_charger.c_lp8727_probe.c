#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lp8727_platform_data {int dummy; } ;
struct lp8727_chg {TYPE_1__* dev; int /*<<< orphan*/  xfer_lock; struct lp8727_platform_data* pdata; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 scalar_t__ IS_ERR (struct lp8727_platform_data*) ; 
 int PTR_ERR (struct lp8727_platform_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct lp8727_platform_data* dev_get_platdata (TYPE_1__*) ; 
 struct lp8727_chg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp8727_chg*) ; 
 int lp8727_init_device (struct lp8727_chg*) ; 
 struct lp8727_platform_data* lp8727_parse_dt (TYPE_1__*) ; 
 int lp8727_register_psy (struct lp8727_chg*) ; 
 int lp8727_setup_irq (struct lp8727_chg*) ; 
 int /*<<< orphan*/  lp8727_unregister_psy (struct lp8727_chg*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8727_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct lp8727_chg *pchg;
	struct lp8727_platform_data *pdata;
	int ret;

	if (!i2c_check_functionality(cl->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EIO;

	if (cl->dev.of_node) {
		pdata = lp8727_parse_dt(&cl->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	} else {
		pdata = dev_get_platdata(&cl->dev);
	}

	pchg = devm_kzalloc(&cl->dev, sizeof(*pchg), GFP_KERNEL);
	if (!pchg)
		return -ENOMEM;

	pchg->client = cl;
	pchg->dev = &cl->dev;
	pchg->pdata = pdata;
	i2c_set_clientdata(cl, pchg);

	mutex_init(&pchg->xfer_lock);

	ret = lp8727_init_device(pchg);
	if (ret) {
		dev_err(pchg->dev, "i2c communication err: %d", ret);
		return ret;
	}

	ret = lp8727_register_psy(pchg);
	if (ret) {
		dev_err(pchg->dev, "power supplies register err: %d", ret);
		return ret;
	}

	ret = lp8727_setup_irq(pchg);
	if (ret) {
		dev_err(pchg->dev, "irq handler err: %d", ret);
		lp8727_unregister_psy(pchg);
		return ret;
	}

	return 0;
}