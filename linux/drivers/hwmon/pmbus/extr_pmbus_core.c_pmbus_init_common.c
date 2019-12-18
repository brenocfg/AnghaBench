#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmbus_driver_info {int (* identify ) (struct i2c_client*,struct pmbus_driver_info*) ;int pages; } ;
struct pmbus_data {int has_status_word; TYPE_1__* info; int /*<<< orphan*/  read_status; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  flags; struct device dev; } ;
struct TYPE_2__ {scalar_t__ pages; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_CLIENT_PEC ; 
 int PB_CAPABILITY_ERROR_CHECK ; 
 int /*<<< orphan*/  PMBUS_CAPABILITY ; 
 int PMBUS_PAGES ; 
 int /*<<< orphan*/  PMBUS_STATUS_BYTE ; 
 int /*<<< orphan*/  PMBUS_STATUS_WORD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmbus_clear_fault_page (struct i2c_client*,int) ; 
 int /*<<< orphan*/  pmbus_clear_faults (struct i2c_client*) ; 
 int pmbus_identify_common (struct i2c_client*,struct pmbus_data*,int) ; 
 int /*<<< orphan*/  pmbus_read_status_byte ; 
 int /*<<< orphan*/  pmbus_read_status_word ; 
 int stub1 (struct i2c_client*,struct pmbus_driver_info*) ; 

__attribute__((used)) static int pmbus_init_common(struct i2c_client *client, struct pmbus_data *data,
			     struct pmbus_driver_info *info)
{
	struct device *dev = &client->dev;
	int page, ret;

	/*
	 * Some PMBus chips don't support PMBUS_STATUS_WORD, so try
	 * to use PMBUS_STATUS_BYTE instead if that is the case.
	 * Bail out if both registers are not supported.
	 */
	data->read_status = pmbus_read_status_word;
	ret = i2c_smbus_read_word_data(client, PMBUS_STATUS_WORD);
	if (ret < 0 || ret == 0xffff) {
		data->read_status = pmbus_read_status_byte;
		ret = i2c_smbus_read_byte_data(client, PMBUS_STATUS_BYTE);
		if (ret < 0 || ret == 0xff) {
			dev_err(dev, "PMBus status register not found\n");
			return -ENODEV;
		}
	} else {
		data->has_status_word = true;
	}

	/* Enable PEC if the controller supports it */
	ret = i2c_smbus_read_byte_data(client, PMBUS_CAPABILITY);
	if (ret >= 0 && (ret & PB_CAPABILITY_ERROR_CHECK))
		client->flags |= I2C_CLIENT_PEC;

	if (data->info->pages)
		pmbus_clear_faults(client);
	else
		pmbus_clear_fault_page(client, -1);

	if (info->identify) {
		ret = (*info->identify)(client, info);
		if (ret < 0) {
			dev_err(dev, "Chip identification failed\n");
			return ret;
		}
	}

	if (info->pages <= 0 || info->pages > PMBUS_PAGES) {
		dev_err(dev, "Bad number of PMBus pages: %d\n", info->pages);
		return -ENODEV;
	}

	for (page = 0; page < info->pages; page++) {
		ret = pmbus_identify_common(client, data, page);
		if (ret < 0) {
			dev_err(dev, "Failed to identify chip capabilities\n");
			return ret;
		}
	}
	return 0;
}