#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_4__ dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_10__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ EE1004_ADDR_SET_PAGE ; 
 int /*<<< orphan*/  EE1004_EEPROM_SIZE ; 
 int EOPNOTSUPP ; 
 int EPFNOSUPPORT ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (TYPE_4__*,char*,char const*) ; 
 int /*<<< orphan*/  ee1004_bus_lock ; 
 int ee1004_current_page ; 
 int ee1004_dev_count ; 
 int ee1004_get_current_page () ; 
 TYPE_1__** ee1004_set_page ; 
 int /*<<< orphan*/  eeprom_attr ; 
 scalar_t__ i2c_adapter_id (int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* i2c_new_dummy_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i2c_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ee1004_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int err, cnr = 0;
	const char *slow = NULL;

	/* Make sure we can operate on this adapter */
	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
		if (i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
			slow = "word";
		else if (i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_BYTE_DATA))
			slow = "byte";
		else
			return -EPFNOSUPPORT;
	}

	/* Use 2 dummy devices for page select command */
	mutex_lock(&ee1004_bus_lock);
	if (++ee1004_dev_count == 1) {
		for (cnr = 0; cnr < 2; cnr++) {
			ee1004_set_page[cnr] = i2c_new_dummy_device(client->adapter,
						EE1004_ADDR_SET_PAGE + cnr);
			if (IS_ERR(ee1004_set_page[cnr])) {
				dev_err(&client->dev,
					"address 0x%02x unavailable\n",
					EE1004_ADDR_SET_PAGE + cnr);
				err = PTR_ERR(ee1004_set_page[cnr]);
				goto err_clients;
			}
		}
	} else if (i2c_adapter_id(client->adapter) !=
		   i2c_adapter_id(ee1004_set_page[0]->adapter)) {
		dev_err(&client->dev,
			"Driver only supports devices on a single I2C bus\n");
		err = -EOPNOTSUPP;
		goto err_clients;
	}

	/* Remember current page to avoid unneeded page select */
	err = ee1004_get_current_page();
	if (err < 0)
		goto err_clients;
	ee1004_current_page = err;
	dev_dbg(&client->dev, "Currently selected page: %d\n",
		ee1004_current_page);
	mutex_unlock(&ee1004_bus_lock);

	/* Create the sysfs eeprom file */
	err = sysfs_create_bin_file(&client->dev.kobj, &eeprom_attr);
	if (err)
		goto err_clients_lock;

	dev_info(&client->dev,
		 "%u byte EE1004-compliant SPD EEPROM, read-only\n",
		 EE1004_EEPROM_SIZE);
	if (slow)
		dev_notice(&client->dev,
			   "Falling back to %s reads, performance will suffer\n",
			   slow);

	return 0;

 err_clients_lock:
	mutex_lock(&ee1004_bus_lock);
 err_clients:
	if (--ee1004_dev_count == 0) {
		for (cnr--; cnr >= 0; cnr--) {
			i2c_unregister_device(ee1004_set_page[cnr]);
			ee1004_set_page[cnr] = NULL;
		}
	}
	mutex_unlock(&ee1004_bus_lock);

	return err;
}