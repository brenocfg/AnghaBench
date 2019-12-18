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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct emc2103_data {int fan_multiplier; int fan_rpm_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FAN_CONF1 ; 
 struct emc2103_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ read_u8_from_i2c (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void read_fan_config_from_i2c(struct i2c_client *client)

{
	struct emc2103_data *data = i2c_get_clientdata(client);
	u8 conf1;

	if (read_u8_from_i2c(client, REG_FAN_CONF1, &conf1) < 0)
		return;

	data->fan_multiplier = 1 << ((conf1 & 0x60) >> 5);
	data->fan_rpm_control = (conf1 & 0x80) != 0;
}