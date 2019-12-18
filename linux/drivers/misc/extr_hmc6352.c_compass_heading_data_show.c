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
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int compass_command (struct i2c_client*,char) ; 
 int /*<<< orphan*/  compass_mutex ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int i2c_master_recv (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t compass_heading_data_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char i2c_data[2];
	int ret;

	mutex_lock(&compass_mutex);
	ret = compass_command(client, 'A');
	if (ret != 1) {
		mutex_unlock(&compass_mutex);
		return ret;
	}
	msleep(10); /* sending 'A' cmd we need to wait for 7-10 millisecs */
	ret = i2c_master_recv(client, i2c_data, 2);
	mutex_unlock(&compass_mutex);
	if (ret < 0) {
		dev_warn(dev, "i2c read data cmd failed\n");
		return ret;
	}
	ret = (i2c_data[0] << 8) | i2c_data[1];
	return sprintf(buf, "%d.%d\n", ret/10, ret%10);
}