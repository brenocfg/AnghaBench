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
struct sht3x_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sht3x_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sht3x_cmd_read_status_reg ; 
 int sht3x_read_from_command (struct i2c_client*,struct sht3x_data*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int status_register_read(struct device *dev,
				struct device_attribute *attr,
				char *buffer, int length)
{
	int ret;
	struct sht3x_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	ret = sht3x_read_from_command(client, data, sht3x_cmd_read_status_reg,
				      buffer, length, 0);

	return ret;
}