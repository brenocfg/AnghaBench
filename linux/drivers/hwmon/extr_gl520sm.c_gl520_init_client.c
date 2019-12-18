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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gl520_data {int alarm_mask; int two_temps; scalar_t__* fan_min; int beep_mask; int /*<<< orphan*/  vrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL520_REG_BEEP_MASK ; 
 int /*<<< orphan*/  GL520_REG_CONF ; 
 int extra_sensor_type ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_update_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct gl520_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static void gl520_init_client(struct i2c_client *client)
{
	struct gl520_data *data = i2c_get_clientdata(client);
	u8 oldconf, conf;

	conf = oldconf = gl520_read_value(client, GL520_REG_CONF);

	data->alarm_mask = 0xff;
	data->vrm = vid_which_vrm();

	if (extra_sensor_type == 1)
		conf &= ~0x10;
	else if (extra_sensor_type == 2)
		conf |= 0x10;
	data->two_temps = !(conf & 0x10);

	/* If IRQ# is disabled, we can safely force comparator mode */
	if (!(conf & 0x20))
		conf &= 0xf7;

	/* Enable monitoring if needed */
	conf |= 0x40;

	if (conf != oldconf)
		gl520_write_value(client, GL520_REG_CONF, conf);

	gl520_update_device(&(client->dev));

	if (data->fan_min[0] == 0)
		data->alarm_mask &= ~0x20;
	if (data->fan_min[1] == 0)
		data->alarm_mask &= ~0x40;

	data->beep_mask &= data->alarm_mask;
	gl520_write_value(client, GL520_REG_BEEP_MASK, data->beep_mask);
}