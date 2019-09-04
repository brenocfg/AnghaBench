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

/* Variables and functions */
 int /*<<< orphan*/  ET8EK8_REG_8BIT ; 
 int et8ek8_i2c_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et8ek8_stream_on(struct et8ek8_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);

	return et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT, 0x1252, 0xb0);
}