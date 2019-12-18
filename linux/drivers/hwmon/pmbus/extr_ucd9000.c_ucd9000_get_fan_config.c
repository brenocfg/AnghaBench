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
struct ucd9000_data {int** fan_data; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int PB_FAN_2_INSTALLED ; 
 int /*<<< orphan*/  pmbus_get_driver_info (struct i2c_client*) ; 
 struct ucd9000_data* to_ucd9000_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucd9000_get_fan_config(struct i2c_client *client, int fan)
{
	int fan_config = 0;
	struct ucd9000_data *data
	  = to_ucd9000_data(pmbus_get_driver_info(client));

	if (data->fan_data[fan][3] & 1)
		fan_config |= PB_FAN_2_INSTALLED;   /* Use lower bit position */

	/* Pulses/revolution */
	fan_config |= (data->fan_data[fan][3] & 0x06) >> 1;

	return fan_config;
}