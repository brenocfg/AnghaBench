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
struct seq_file {int dummy; } ;
struct m41t80_data {int features; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int M41T80_FEATURE_BL ; 
 int M41T80_FLAGS_BATT_LOW ; 
 int /*<<< orphan*/  M41T80_REG_FLAGS ; 
 struct m41t80_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int m41t80_rtc_proc(struct device *dev, struct seq_file *seq)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct m41t80_data *clientdata = i2c_get_clientdata(client);
	int reg;

	if (clientdata->features & M41T80_FEATURE_BL) {
		reg = i2c_smbus_read_byte_data(client, M41T80_REG_FLAGS);
		if (reg < 0)
			return reg;
		seq_printf(seq, "battery\t\t: %s\n",
			   (reg & M41T80_FLAGS_BATT_LOW) ? "exhausted" : "ok");
	}
	return 0;
}