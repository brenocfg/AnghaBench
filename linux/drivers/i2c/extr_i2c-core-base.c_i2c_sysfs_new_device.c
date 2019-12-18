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
struct i2c_client {int /*<<< orphan*/  detected; } ;
struct i2c_board_info {int addr; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int /*<<< orphan*/  userspace_clients_lock; int /*<<< orphan*/  userspace_clients; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int I2C_ADDR_OFFSET_SLAVE ; 
 int I2C_ADDR_OFFSET_TEN_BIT ; 
 int /*<<< orphan*/  I2C_CLIENT_SLAVE ; 
 int /*<<< orphan*/  I2C_CLIENT_TEN ; 
 int I2C_NAME_SIZE ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 size_t PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* i2c_new_client_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*,char*) ; 
 char* strchr (char const*,char) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 

__attribute__((used)) static ssize_t
i2c_sysfs_new_device(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	struct i2c_adapter *adap = to_i2c_adapter(dev);
	struct i2c_board_info info;
	struct i2c_client *client;
	char *blank, end;
	int res;

	memset(&info, 0, sizeof(struct i2c_board_info));

	blank = strchr(buf, ' ');
	if (!blank) {
		dev_err(dev, "%s: Missing parameters\n", "new_device");
		return -EINVAL;
	}
	if (blank - buf > I2C_NAME_SIZE - 1) {
		dev_err(dev, "%s: Invalid device name\n", "new_device");
		return -EINVAL;
	}
	memcpy(info.type, buf, blank - buf);

	/* Parse remaining parameters, reject extra parameters */
	res = sscanf(++blank, "%hi%c", &info.addr, &end);
	if (res < 1) {
		dev_err(dev, "%s: Can't parse I2C address\n", "new_device");
		return -EINVAL;
	}
	if (res > 1  && end != '\n') {
		dev_err(dev, "%s: Extra parameters\n", "new_device");
		return -EINVAL;
	}

	if ((info.addr & I2C_ADDR_OFFSET_TEN_BIT) == I2C_ADDR_OFFSET_TEN_BIT) {
		info.addr &= ~I2C_ADDR_OFFSET_TEN_BIT;
		info.flags |= I2C_CLIENT_TEN;
	}

	if (info.addr & I2C_ADDR_OFFSET_SLAVE) {
		info.addr &= ~I2C_ADDR_OFFSET_SLAVE;
		info.flags |= I2C_CLIENT_SLAVE;
	}

	client = i2c_new_client_device(adap, &info);
	if (IS_ERR(client))
		return PTR_ERR(client);

	/* Keep track of the added device */
	mutex_lock(&adap->userspace_clients_lock);
	list_add_tail(&client->detected, &adap->userspace_clients);
	mutex_unlock(&adap->userspace_clients_lock);
	dev_info(dev, "%s: Instantiated device %s at 0x%02hx\n", "new_device",
		 info.type, info.addr);

	return count;
}