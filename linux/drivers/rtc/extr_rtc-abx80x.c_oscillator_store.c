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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ABX8XX_CFG_KEY_OSC ; 
 int ABX8XX_OSC_OSEL ; 
 int /*<<< orphan*/  ABX8XX_REG_CFG_KEY ; 
 int /*<<< orphan*/  ABX8XX_REG_OSC ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t oscillator_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev->parent);
	int retval, flags, rc_mode = 0;

	if (strncmp(buf, "rc", 2) == 0) {
		rc_mode = 1;
	} else if (strncmp(buf, "xtal", 4) == 0) {
		rc_mode = 0;
	} else {
		dev_err(dev, "Oscillator selection value outside permitted ones\n");
		return -EINVAL;
	}

	flags =  i2c_smbus_read_byte_data(client, ABX8XX_REG_OSC);
	if (flags < 0)
		return flags;

	if (rc_mode == 0)
		flags &= ~(ABX8XX_OSC_OSEL);
	else
		flags |= (ABX8XX_OSC_OSEL);

	/* Unlock write access on Oscillator Control register */
	retval = i2c_smbus_write_byte_data(client, ABX8XX_REG_CFG_KEY,
					   ABX8XX_CFG_KEY_OSC);
	if (retval < 0) {
		dev_err(dev, "Failed to write CONFIG_KEY register\n");
		return retval;
	}

	retval = i2c_smbus_write_byte_data(client, ABX8XX_REG_OSC, flags);
	if (retval < 0) {
		dev_err(dev, "Failed to write Oscillator Control register\n");
		return retval;
	}

	return retval ? retval : count;
}