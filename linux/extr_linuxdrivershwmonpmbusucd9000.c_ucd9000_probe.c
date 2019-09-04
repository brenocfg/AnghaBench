#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct pmbus_driver_info {int pages; int* func; int /*<<< orphan*/  read_byte_data; } ;
struct ucd9000_data {char** fan_data; struct pmbus_driver_info info; } ;
struct i2c_device_id {int driver_data; scalar_t__* name; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_BLOCK_MAX ; 
 int PMBUS_HAVE_FAN12 ; 
 int PMBUS_HAVE_FAN34 ; 
 int PMBUS_HAVE_IOUT ; 
 int PMBUS_HAVE_STATUS_FAN12 ; 
 int PMBUS_HAVE_STATUS_FAN34 ; 
 int PMBUS_HAVE_STATUS_IOUT ; 
 int PMBUS_HAVE_STATUS_TEMP ; 
 int PMBUS_HAVE_STATUS_VOUT ; 
 int PMBUS_HAVE_TEMP ; 
 int PMBUS_HAVE_TEMP2 ; 
 int PMBUS_HAVE_VOUT ; 
 int /*<<< orphan*/  UCD9000_DEVICE_ID ; 
 int /*<<< orphan*/  UCD9000_FAN_CONFIG ; 
 int /*<<< orphan*/  UCD9000_FAN_CONFIG_INDEX ; 
 int /*<<< orphan*/  UCD9000_MONITOR_CONFIG ; 
#define  UCD9000_MON_CURRENT 131 
 int UCD9000_MON_PAGE (char) ; 
#define  UCD9000_MON_TEMPERATURE 130 
 int UCD9000_MON_TYPE (char) ; 
#define  UCD9000_MON_VOLTAGE 129 
#define  UCD9000_MON_VOLTAGE_HW 128 
 int UCD9000_NUM_FAN ; 
 int /*<<< orphan*/  UCD9000_NUM_PAGES ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  dev_notice (TYPE_1__*,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 struct ucd9000_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strncasecmp (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 int ucd9000 ; 
 struct i2c_device_id* ucd9000_id ; 
 int ucd9000_init_debugfs (struct i2c_client*,struct i2c_device_id const*,struct ucd9000_data*) ; 
 int /*<<< orphan*/  ucd9000_probe_gpio (struct i2c_client*,struct i2c_device_id const*,struct ucd9000_data*) ; 
 int /*<<< orphan*/  ucd9000_read_byte_data ; 
 scalar_t__ ucd90124 ; 

__attribute__((used)) static int ucd9000_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX + 1];
	struct ucd9000_data *data;
	struct pmbus_driver_info *info;
	const struct i2c_device_id *mid;
	enum chips chip;
	int i, ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA))
		return -ENODEV;

	ret = i2c_smbus_read_block_data(client, UCD9000_DEVICE_ID,
					block_buffer);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to read device ID\n");
		return ret;
	}
	block_buffer[ret] = '\0';
	dev_info(&client->dev, "Device ID %s\n", block_buffer);

	for (mid = ucd9000_id; mid->name[0]; mid++) {
		if (!strncasecmp(mid->name, block_buffer, strlen(mid->name)))
			break;
	}
	if (!mid->name[0]) {
		dev_err(&client->dev, "Unsupported device\n");
		return -ENODEV;
	}

	if (client->dev.of_node)
		chip = (enum chips)of_device_get_match_data(&client->dev);
	else
		chip = id->driver_data;

	if (chip != ucd9000 && chip != mid->driver_data)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   id->name, mid->name);

	data = devm_kzalloc(&client->dev, sizeof(struct ucd9000_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	info = &data->info;

	ret = i2c_smbus_read_byte_data(client, UCD9000_NUM_PAGES);
	if (ret < 0) {
		dev_err(&client->dev,
			"Failed to read number of active pages\n");
		return ret;
	}
	info->pages = ret;
	if (!info->pages) {
		dev_err(&client->dev, "No pages configured\n");
		return -ENODEV;
	}

	/* The internal temperature sensor is always active */
	info->func[0] = PMBUS_HAVE_TEMP;

	/* Everything else is configurable */
	ret = i2c_smbus_read_block_data(client, UCD9000_MONITOR_CONFIG,
					block_buffer);
	if (ret <= 0) {
		dev_err(&client->dev, "Failed to read configuration data\n");
		return -ENODEV;
	}
	for (i = 0; i < ret; i++) {
		int page = UCD9000_MON_PAGE(block_buffer[i]);

		if (page >= info->pages)
			continue;

		switch (UCD9000_MON_TYPE(block_buffer[i])) {
		case UCD9000_MON_VOLTAGE:
		case UCD9000_MON_VOLTAGE_HW:
			info->func[page] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT;
			break;
		case UCD9000_MON_TEMPERATURE:
			info->func[page] |= PMBUS_HAVE_TEMP2
			  | PMBUS_HAVE_STATUS_TEMP;
			break;
		case UCD9000_MON_CURRENT:
			info->func[page] |= PMBUS_HAVE_IOUT
			  | PMBUS_HAVE_STATUS_IOUT;
			break;
		default:
			break;
		}
	}

	/* Fan configuration */
	if (mid->driver_data == ucd90124) {
		for (i = 0; i < UCD9000_NUM_FAN; i++) {
			i2c_smbus_write_byte_data(client,
						  UCD9000_FAN_CONFIG_INDEX, i);
			ret = i2c_smbus_read_block_data(client,
							UCD9000_FAN_CONFIG,
							data->fan_data[i]);
			if (ret < 0)
				return ret;
		}
		i2c_smbus_write_byte_data(client, UCD9000_FAN_CONFIG_INDEX, 0);

		info->read_byte_data = ucd9000_read_byte_data;
		info->func[0] |= PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12
		  | PMBUS_HAVE_FAN34 | PMBUS_HAVE_STATUS_FAN34;
	}

	ucd9000_probe_gpio(client, mid, data);

	ret = pmbus_do_probe(client, mid, info);
	if (ret)
		return ret;

	ret = ucd9000_init_debugfs(client, mid, data);
	if (ret)
		dev_warn(&client->dev, "Failed to register debugfs: %d\n",
			 ret);

	return 0;
}