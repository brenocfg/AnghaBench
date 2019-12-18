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
struct mcp3021_data {int dummy; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct mcp3021_data* i2c_get_clientdata (struct i2c_client*) ; 
 int mcp3021_read16 (struct i2c_client*) ; 
 int sprintf (char*,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int volts_from_reg (struct mcp3021_data*,int) ; 

__attribute__((used)) static ssize_t in0_input_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mcp3021_data *data = i2c_get_clientdata(client);
	int reg, in_input;

	reg = mcp3021_read16(client);
	if (reg < 0)
		return reg;

	in_input = volts_from_reg(data, reg);

	return sprintf(buf, "%d\n", in_input);
}