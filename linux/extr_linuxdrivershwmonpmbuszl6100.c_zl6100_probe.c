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
typedef  char u8 ;
struct pmbus_driver_info {int pages; int* func; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  write_word_data; int /*<<< orphan*/  read_byte_data; int /*<<< orphan*/  read_word_data; } ;
struct zl6100_data {scalar_t__ id; void* access; struct pmbus_driver_info info; int /*<<< orphan*/  delay; } ;
struct i2c_device_id {scalar_t__ driver_data; scalar_t__* name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_BLOCK_MAX ; 
 int PMBUS_HAVE_IOUT ; 
 int PMBUS_HAVE_STATUS_INPUT ; 
 int PMBUS_HAVE_STATUS_IOUT ; 
 int PMBUS_HAVE_STATUS_TEMP ; 
 int PMBUS_HAVE_STATUS_VMON ; 
 int PMBUS_HAVE_STATUS_VOUT ; 
 int PMBUS_HAVE_TEMP ; 
 int PMBUS_HAVE_TEMP2 ; 
 int PMBUS_HAVE_VIN ; 
 int PMBUS_HAVE_VMON ; 
 int PMBUS_HAVE_VOUT ; 
 int /*<<< orphan*/  ZL6100_DEVICE_ID ; 
 int /*<<< orphan*/  ZL6100_MFR_CONFIG ; 
 int ZL6100_MFR_XTEMP_ENABLE ; 
 int /*<<< orphan*/  delay ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 struct zl6100_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,char*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 void* ktime_get () ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strncasecmp (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zl2004 ; 
 struct i2c_device_id* zl6100_id ; 
 int /*<<< orphan*/  zl6100_read_byte_data ; 
 int /*<<< orphan*/  zl6100_read_word_data ; 
 int /*<<< orphan*/  zl6100_wait (struct zl6100_data*) ; 
 int /*<<< orphan*/  zl6100_write_byte ; 
 int /*<<< orphan*/  zl6100_write_word_data ; 
 scalar_t__ zl9101 ; 
 scalar_t__ zl9117 ; 

__attribute__((used)) static int zl6100_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct zl6100_data *data;
	struct pmbus_driver_info *info;
	u8 device_id[I2C_SMBUS_BLOCK_MAX + 1];
	const struct i2c_device_id *mid;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA
				     | I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		return -ENODEV;

	ret = i2c_smbus_read_block_data(client, ZL6100_DEVICE_ID,
					device_id);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to read device ID\n");
		return ret;
	}
	device_id[ret] = '\0';
	dev_info(&client->dev, "Device ID %s\n", device_id);

	mid = NULL;
	for (mid = zl6100_id; mid->name[0]; mid++) {
		if (!strncasecmp(mid->name, device_id, strlen(mid->name)))
			break;
	}
	if (!mid->name[0]) {
		dev_err(&client->dev, "Unsupported device\n");
		return -ENODEV;
	}
	if (id->driver_data != mid->driver_data)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   id->name, mid->name);

	data = devm_kzalloc(&client->dev, sizeof(struct zl6100_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->id = mid->driver_data;

	/*
	 * According to information from the chip vendor, all currently
	 * supported chips are known to require a wait time between I2C
	 * accesses.
	 */
	data->delay = delay;

	/*
	 * Since there was a direct I2C device access above, wait before
	 * accessing the chip again.
	 */
	data->access = ktime_get();
	zl6100_wait(data);

	info = &data->info;

	info->pages = 1;
	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
	  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
	  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;

	/*
	 * ZL2004, ZL9101M, and ZL9117M support monitoring an extra voltage
	 * (VMON for ZL2004, VDRV for ZL9101M and ZL9117M). Report it as vmon.
	 */
	if (data->id == zl2004 || data->id == zl9101 || data->id == zl9117)
		info->func[0] |= PMBUS_HAVE_VMON | PMBUS_HAVE_STATUS_VMON;

	ret = i2c_smbus_read_word_data(client, ZL6100_MFR_CONFIG);
	if (ret < 0)
		return ret;

	if (ret & ZL6100_MFR_XTEMP_ENABLE)
		info->func[0] |= PMBUS_HAVE_TEMP2;

	data->access = ktime_get();
	zl6100_wait(data);

	info->read_word_data = zl6100_read_word_data;
	info->read_byte_data = zl6100_read_byte_data;
	info->write_word_data = zl6100_write_word_data;
	info->write_byte = zl6100_write_byte;

	return pmbus_do_probe(client, mid, info);
}