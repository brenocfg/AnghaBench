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
typedef  int /*<<< orphan*/  u8 ;
struct ili210x {int /*<<< orphan*/  client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  REG_CALIBRATE ; 
 struct ili210x* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t ili210x_calibrate(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ili210x *priv = i2c_get_clientdata(client);
	unsigned long calibrate;
	int rc;
	u8 cmd = REG_CALIBRATE;

	if (kstrtoul(buf, 10, &calibrate))
		return -EINVAL;

	if (calibrate > 1)
		return -EINVAL;

	if (calibrate) {
		rc = i2c_master_send(priv->client, &cmd, sizeof(cmd));
		if (rc != sizeof(cmd))
			return -EIO;
	}

	return count;
}