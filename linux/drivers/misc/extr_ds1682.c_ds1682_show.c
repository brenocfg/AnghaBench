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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute_2 {scalar_t__ index; int nr; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 scalar_t__ DS1682_REG_ELAPSED ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 unsigned long long le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ds1682_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	unsigned long long val, check;
	__le32 val_le = 0;
	int rc;

	dev_dbg(dev, "ds1682_show() called on %s\n", attr->attr.name);

	/* Read the register */
	rc = i2c_smbus_read_i2c_block_data(client, sattr->index, sattr->nr,
					   (u8 *)&val_le);
	if (rc < 0)
		return -EIO;

	val = le32_to_cpu(val_le);

	if (sattr->index == DS1682_REG_ELAPSED) {
		int retries = 5;

		/* Detect and retry when a tick occurs mid-read */
		do {
			rc = i2c_smbus_read_i2c_block_data(client, sattr->index,
							   sattr->nr,
							   (u8 *)&val_le);
			if (rc < 0 || retries <= 0)
				return -EIO;

			check = val;
			val = le32_to_cpu(val_le);
			retries--;
		} while (val != check && val != (check + 1));
	}

	/* Format the output string and return # of bytes
	 * Special case: the 32 bit regs are time values with 1/4s
	 * resolution, scale them up to milliseconds
	 */
	return sprintf(buf, "%llu\n", (sattr->nr == 4) ? (val * 250) : val);
}