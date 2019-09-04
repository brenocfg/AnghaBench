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
typedef  int u8 ;
struct w83795_data {scalar_t__ chip_type; int has_in; int has_fan; int enable_dts; int has_dts; int has_gain; int has_pwm; int enable_beep; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  bank; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int OVT_CFG_SEL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W83795_REG_BANKSEL ; 
 int /*<<< orphan*/  W83795_REG_DTSC ; 
 int /*<<< orphan*/  W83795_REG_DTSE ; 
 int /*<<< orphan*/  W83795_REG_FANIN_CTRL1 ; 
 int /*<<< orphan*/  W83795_REG_FANIN_CTRL2 ; 
 int /*<<< orphan*/  W83795_REG_OVT_CFG ; 
 int /*<<< orphan*/  W83795_REG_PECI_TBASE (int) ; 
 int /*<<< orphan*/  W83795_REG_TEMP_CTRL1 ; 
 int /*<<< orphan*/  W83795_REG_TEMP_CTRL2 ; 
 int /*<<< orphan*/  W83795_REG_VMIGB_CTRL ; 
 int /*<<< orphan*/  W83795_REG_VOLT_CTRL1 ; 
 int /*<<< orphan*/  W83795_REG_VOLT_CTRL2 ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  device_create_file ; 
 int /*<<< orphan*/  device_remove_file_wrapper ; 
 struct w83795_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct w83795_data*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83795_apply_temp_config (struct w83795_data*,int,int,int) ; 
 int /*<<< orphan*/  w83795_check_dynamic_in_limits (struct i2c_client*) ; 
 int w83795_handle_files (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_init_client (struct i2c_client*) ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ w83795g ; 

__attribute__((used)) static int w83795_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int i;
	u8 tmp;
	struct device *dev = &client->dev;
	struct w83795_data *data;
	int err;

	data = devm_kzalloc(dev, sizeof(struct w83795_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->chip_type = id->driver_data;
	data->bank = i2c_smbus_read_byte_data(client, W83795_REG_BANKSEL);
	mutex_init(&data->update_lock);

	/* Initialize the chip */
	w83795_init_client(client);

	/* Check which voltages and fans are present */
	data->has_in = w83795_read(client, W83795_REG_VOLT_CTRL1)
		     | (w83795_read(client, W83795_REG_VOLT_CTRL2) << 8);
	data->has_fan = w83795_read(client, W83795_REG_FANIN_CTRL1)
		      | (w83795_read(client, W83795_REG_FANIN_CTRL2) << 8);

	/* Check which analog temperatures and extra voltages are present */
	tmp = w83795_read(client, W83795_REG_TEMP_CTRL1);
	if (tmp & 0x20)
		data->enable_dts = 1;
	w83795_apply_temp_config(data, (tmp >> 2) & 0x3, 5, 16);
	w83795_apply_temp_config(data, tmp & 0x3, 4, 15);
	tmp = w83795_read(client, W83795_REG_TEMP_CTRL2);
	w83795_apply_temp_config(data, tmp >> 6, 3, 20);
	w83795_apply_temp_config(data, (tmp >> 4) & 0x3, 2, 19);
	w83795_apply_temp_config(data, (tmp >> 2) & 0x3, 1, 18);
	w83795_apply_temp_config(data, tmp & 0x3, 0, 17);

	/* Check DTS enable status */
	if (data->enable_dts) {
		if (1 & w83795_read(client, W83795_REG_DTSC))
			data->enable_dts |= 2;
		data->has_dts = w83795_read(client, W83795_REG_DTSE);
	}

	/* Report PECI Tbase values */
	if (data->enable_dts == 1) {
		for (i = 0; i < 8; i++) {
			if (!(data->has_dts & (1 << i)))
				continue;
			tmp = w83795_read(client, W83795_REG_PECI_TBASE(i));
			dev_info(&client->dev,
				 "PECI agent %d Tbase temperature: %u\n",
				 i + 1, (unsigned int)tmp & 0x7f);
		}
	}

	data->has_gain = w83795_read(client, W83795_REG_VMIGB_CTRL) & 0x0f;

	/* pwm and smart fan */
	if (data->chip_type == w83795g)
		data->has_pwm = 8;
	else
		data->has_pwm = 2;

	/* Check if BEEP pin is available */
	if (data->chip_type == w83795g) {
		/* The W83795G has a dedicated BEEP pin */
		data->enable_beep = 1;
	} else {
		/*
		 * The W83795ADG has a shared pin for OVT# and BEEP, so you
		 * can't have both
		 */
		tmp = w83795_read(client, W83795_REG_OVT_CFG);
		if ((tmp & OVT_CFG_SEL) == 0)
			data->enable_beep = 1;
	}

	err = w83795_handle_files(dev, device_create_file);
	if (err)
		goto exit_remove;

	if (data->chip_type == w83795g)
		w83795_check_dynamic_in_limits(client);

	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	w83795_handle_files(dev, device_remove_file_wrapper);
	return err;
}