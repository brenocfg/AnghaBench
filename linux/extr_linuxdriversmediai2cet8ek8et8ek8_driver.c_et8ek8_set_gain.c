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
struct et8ek8_sensor {int /*<<< orphan*/  subdev; } ;
struct et8ek8_gain {int analog; int digital; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ET8EK8_REG_8BIT ; 
 struct et8ek8_gain* et8ek8_gain_table ; 
 int et8ek8_i2c_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et8ek8_set_gain(struct et8ek8_sensor *sensor, s32 gain)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	struct et8ek8_gain new;
	int r;

	new = et8ek8_gain_table[gain];

	/* FIXME: optimise I2C writes! */
	r = et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT,
				0x124a, new.analog >> 8);
	if (r)
		return r;
	r = et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT,
				0x1249, new.analog & 0xff);
	if (r)
		return r;

	r = et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT,
				0x124d, new.digital >> 8);
	if (r)
		return r;
	r = et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT,
				0x124c, new.digital & 0xff);

	return r;
}