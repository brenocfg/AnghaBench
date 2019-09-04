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
struct dme1737_data {int vrm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct dme1737_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t vrm_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct dme1737_data *data = i2c_get_clientdata(client);

	return sprintf(buf, "%d\n", data->vrm);
}