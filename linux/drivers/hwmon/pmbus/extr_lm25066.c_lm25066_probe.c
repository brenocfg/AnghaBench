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
struct pmbus_driver_info {int pages; int* func; int /*<<< orphan*/ * b; int /*<<< orphan*/ * m; int /*<<< orphan*/ * R; int /*<<< orphan*/  write_word_data; int /*<<< orphan*/  read_word_data; int /*<<< orphan*/  read_byte_data; void** format; } ;
struct lm25066_data {size_t id; int rlimit; struct pmbus_driver_info info; } ;
struct i2c_device_id {size_t driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct __coeff {int /*<<< orphan*/  b; int /*<<< orphan*/  m; int /*<<< orphan*/  R; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int /*<<< orphan*/  LM25066_DEVICE_SETUP ; 
 int LM25066_DEV_SETUP_CL ; 
 int PMBUS_HAVE_IIN ; 
 int PMBUS_HAVE_PIN ; 
 int PMBUS_HAVE_SAMPLES ; 
 int PMBUS_HAVE_STATUS_INPUT ; 
 int PMBUS_HAVE_STATUS_TEMP ; 
 int PMBUS_HAVE_STATUS_VMON ; 
 int PMBUS_HAVE_STATUS_VOUT ; 
 int PMBUS_HAVE_TEMP ; 
 int PMBUS_HAVE_VIN ; 
 int PMBUS_HAVE_VMON ; 
 int PMBUS_HAVE_VOUT ; 
 size_t PSC_CURRENT_IN ; 
 size_t PSC_CURRENT_IN_L ; 
 size_t PSC_POWER ; 
 size_t PSC_POWER_L ; 
 size_t PSC_TEMPERATURE ; 
 size_t PSC_VOLTAGE_IN ; 
 size_t PSC_VOLTAGE_OUT ; 
 struct lm25066_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* direct ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 size_t lm25056 ; 
 int /*<<< orphan*/  lm25056_read_byte_data ; 
 int /*<<< orphan*/  lm25056_read_word_data ; 
 struct __coeff** lm25066_coeff ; 
 int /*<<< orphan*/  lm25066_read_word_data ; 
 int /*<<< orphan*/  lm25066_write_word_data ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 

__attribute__((used)) static int lm25066_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	int config;
	struct lm25066_data *data;
	struct pmbus_driver_info *info;
	struct __coeff *coeff;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA))
		return -ENODEV;

	data = devm_kzalloc(&client->dev, sizeof(struct lm25066_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	config = i2c_smbus_read_byte_data(client, LM25066_DEVICE_SETUP);
	if (config < 0)
		return config;

	data->id = id->driver_data;
	info = &data->info;

	info->pages = 1;
	info->format[PSC_VOLTAGE_IN] = direct;
	info->format[PSC_VOLTAGE_OUT] = direct;
	info->format[PSC_CURRENT_IN] = direct;
	info->format[PSC_TEMPERATURE] = direct;
	info->format[PSC_POWER] = direct;

	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VMON
	  | PMBUS_HAVE_PIN | PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT
	  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_SAMPLES;

	if (data->id == lm25056) {
		info->func[0] |= PMBUS_HAVE_STATUS_VMON;
		info->read_word_data = lm25056_read_word_data;
		info->read_byte_data = lm25056_read_byte_data;
		data->rlimit = 0x0fff;
	} else {
		info->func[0] |= PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		info->read_word_data = lm25066_read_word_data;
		data->rlimit = 0x0fff;
	}
	info->write_word_data = lm25066_write_word_data;

	coeff = &lm25066_coeff[data->id][0];
	info->m[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].m;
	info->b[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].b;
	info->R[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].R;
	info->m[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].m;
	info->b[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].b;
	info->R[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].R;
	info->m[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].m;
	info->b[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].b;
	info->R[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].R;
	info->R[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].R;
	info->R[PSC_POWER] = coeff[PSC_POWER].R;
	if (config & LM25066_DEV_SETUP_CL) {
		info->m[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN_L].m;
		info->b[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN_L].b;
		info->m[PSC_POWER] = coeff[PSC_POWER_L].m;
		info->b[PSC_POWER] = coeff[PSC_POWER_L].b;
	} else {
		info->m[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].m;
		info->b[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].b;
		info->m[PSC_POWER] = coeff[PSC_POWER].m;
		info->b[PSC_POWER] = coeff[PSC_POWER].b;
	}

	return pmbus_do_probe(client, id, info);
}