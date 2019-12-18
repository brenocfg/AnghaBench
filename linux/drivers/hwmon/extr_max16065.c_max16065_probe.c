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
struct max16065_data {int num_adc; int have_current; int curr_gain; int /*<<< orphan*/ ** groups; int /*<<< orphan*/ * range; int /*<<< orphan*/ ** limit; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {size_t driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int /*<<< orphan*/  LIMIT_TO_MV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX16065_CURR_CONTROL ; 
 int MAX16065_CURR_ENABLE ; 
 int /*<<< orphan*/  MAX16065_LIMIT (int,int) ; 
 size_t MAX16065_NUM_ADC ; 
 int MAX16065_NUM_LIMIT ; 
 int /*<<< orphan*/  MAX16065_SCALE (int) ; 
 int /*<<< orphan*/  MAX16065_SW_ENABLE ; 
 int MAX16065_WARNING_OV ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct max16065_data*,int /*<<< orphan*/ **) ; 
 struct max16065_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * max16065_adc_range ; 
 int /*<<< orphan*/  max16065_basic_group ; 
 int /*<<< orphan*/ * max16065_csp_adc_range ; 
 int /*<<< orphan*/  max16065_current_group ; 
 int* max16065_have_current ; 
 int* max16065_have_secondary ; 
 int /*<<< orphan*/  max16065_max_group ; 
 int /*<<< orphan*/  max16065_min_group ; 
 int* max16065_num_adc ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int max16065_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct max16065_data *data;
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	int i, j, val;
	bool have_secondary;		/* true if chip has secondary limits */
	bool secondary_is_max = false;	/* secondary limits reflect max */
	int groups = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_WORD_DATA))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (unlikely(!data))
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	data->num_adc = max16065_num_adc[id->driver_data];
	data->have_current = max16065_have_current[id->driver_data];
	have_secondary = max16065_have_secondary[id->driver_data];

	if (have_secondary) {
		val = i2c_smbus_read_byte_data(client, MAX16065_SW_ENABLE);
		if (unlikely(val < 0))
			return val;
		secondary_is_max = val & MAX16065_WARNING_OV;
	}

	/* Read scale registers, convert to range */
	for (i = 0; i < DIV_ROUND_UP(data->num_adc, 4); i++) {
		val = i2c_smbus_read_byte_data(client, MAX16065_SCALE(i));
		if (unlikely(val < 0))
			return val;
		for (j = 0; j < 4 && i * 4 + j < data->num_adc; j++) {
			data->range[i * 4 + j] =
			  max16065_adc_range[(val >> (j * 2)) & 0x3];
		}
	}

	/* Read limits */
	for (i = 0; i < MAX16065_NUM_LIMIT; i++) {
		if (i == 0 && !have_secondary)
			continue;

		for (j = 0; j < data->num_adc; j++) {
			val = i2c_smbus_read_byte_data(client,
						       MAX16065_LIMIT(i, j));
			if (unlikely(val < 0))
				return val;
			data->limit[i][j] = LIMIT_TO_MV(val, data->range[j]);
		}
	}

	/* sysfs hooks */
	data->groups[groups++] = &max16065_basic_group;
	if (have_secondary)
		data->groups[groups++] = secondary_is_max ?
			&max16065_max_group : &max16065_min_group;

	if (data->have_current) {
		val = i2c_smbus_read_byte_data(client, MAX16065_CURR_CONTROL);
		if (unlikely(val < 0))
			return val;
		if (val & MAX16065_CURR_ENABLE) {
			/*
			 * Current gain is 6, 12, 24, 48 based on values in
			 * bit 2,3.
			 */
			data->curr_gain = 6 << ((val >> 2) & 0x03);
			data->range[MAX16065_NUM_ADC]
			  = max16065_csp_adc_range[(val >> 1) & 0x01];
			data->groups[groups++] = &max16065_current_group;
		} else {
			data->have_current = false;
		}
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}