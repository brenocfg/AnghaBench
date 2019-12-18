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
struct regmap {int dummy; } ;
struct mpu3050 {TYPE_1__* i2cmux; } ;
struct i2c_device_id {char* name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {struct mpu3050* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int I2C_MUX_GATE ; 
 int I2C_MUX_LOCKED ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_mux_add_adapter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* i2c_mux_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpu3050* iio_priv (int /*<<< orphan*/ ) ; 
 int mpu3050_common_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mpu3050_i2c_bypass_deselect ; 
 int /*<<< orphan*/  mpu3050_i2c_bypass_select ; 
 int /*<<< orphan*/  mpu3050_i2c_regmap_config ; 

__attribute__((used)) static int mpu3050_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct regmap *regmap;
	const char *name;
	struct mpu3050 *mpu3050;
	int ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EOPNOTSUPP;

	if (id)
		name = id->name;
	else
		return -ENODEV;

	regmap = devm_regmap_init_i2c(client, &mpu3050_i2c_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Failed to register i2c regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	ret = mpu3050_common_probe(&client->dev, regmap, client->irq, name);
	if (ret)
		return ret;

	/* The main driver is up, now register the I2C mux */
	mpu3050 = iio_priv(dev_get_drvdata(&client->dev));
	mpu3050->i2cmux = i2c_mux_alloc(client->adapter, &client->dev,
					1, 0, I2C_MUX_LOCKED | I2C_MUX_GATE,
					mpu3050_i2c_bypass_select,
					mpu3050_i2c_bypass_deselect);
	/* Just fail the mux, there is no point in killing the driver */
	if (!mpu3050->i2cmux)
		dev_err(&client->dev, "failed to allocate I2C mux\n");
	else {
		mpu3050->i2cmux->priv = mpu3050;
		/* Ignore failure, not critical */
		i2c_mux_add_adapter(mpu3050->i2cmux, 0, 0, 0);
	}

	return 0;
}