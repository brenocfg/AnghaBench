#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct inv_mpu6050_state {int chip_type; TYPE_3__* muxc; } ;
struct i2c_device_id {char* name; scalar_t__ driver_data; } ;
struct TYPE_10__ {scalar_t__ of_node; } ;
struct i2c_client {char* name; TYPE_1__ dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; } ;
typedef  enum inv_devices { ____Placeholder_inv_devices } inv_devices ;
struct TYPE_11__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_1__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int I2C_MUX_GATE ; 
 int I2C_MUX_LOCKED ; 
#define  INV_ICM20602 129 
#define  INV_ICM20608 128 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (TYPE_1__*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_mux_add_adapter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* i2c_mux_alloc (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (TYPE_3__*) ; 
 struct inv_mpu6050_state* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inv_mpu6050_deselect_bypass ; 
 int /*<<< orphan*/  inv_mpu6050_select_bypass ; 
 int inv_mpu_acpi_create_mux_client (struct i2c_client*) ; 
 int inv_mpu_core_probe (struct regmap*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 
 char* inv_mpu_match_acpi_device (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  inv_mpu_regmap_config ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 

__attribute__((used)) static int inv_mpu_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct inv_mpu6050_state *st;
	int result;
	enum inv_devices chip_type;
	struct regmap *regmap;
	const char *name;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EOPNOTSUPP;

	if (client->dev.of_node) {
		chip_type = (enum inv_devices)
			of_device_get_match_data(&client->dev);
		name = client->name;
	} else if (id) {
		chip_type = (enum inv_devices)
			id->driver_data;
		name = id->name;
	} else if (ACPI_HANDLE(&client->dev)) {
		name = inv_mpu_match_acpi_device(&client->dev, &chip_type);
		if (!name)
			return -ENODEV;
	} else {
		return -ENOSYS;
	}

	regmap = devm_regmap_init_i2c(client, &inv_mpu_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Failed to register i2c regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	result = inv_mpu_core_probe(regmap, client->irq, name,
				    NULL, chip_type);
	if (result < 0)
		return result;

	st = iio_priv(dev_get_drvdata(&client->dev));
	switch (st->chip_type) {
	case INV_ICM20608:
	case INV_ICM20602:
		/* no i2c auxiliary bus on the chip */
		break;
	default:
		/* declare i2c auxiliary bus */
		st->muxc = i2c_mux_alloc(client->adapter, &client->dev,
					 1, 0, I2C_MUX_LOCKED | I2C_MUX_GATE,
					 inv_mpu6050_select_bypass,
					 inv_mpu6050_deselect_bypass);
		if (!st->muxc)
			return -ENOMEM;
		st->muxc->priv = dev_get_drvdata(&client->dev);
		result = i2c_mux_add_adapter(st->muxc, 0, 0, 0);
		if (result)
			return result;
		result = inv_mpu_acpi_create_mux_client(client);
		if (result)
			goto out_del_mux;
		break;
	}

	return 0;

out_del_mux:
	i2c_mux_del_adapters(st->muxc);
	return result;
}