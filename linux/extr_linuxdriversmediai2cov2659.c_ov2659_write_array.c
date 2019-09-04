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
struct sensor_register {int /*<<< orphan*/  value; scalar_t__ addr; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ov2659_write (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2659_write_array(struct i2c_client *client,
			      const struct sensor_register *regs)
{
	int i, ret = 0;

	for (i = 0; ret == 0 && regs[i].addr; i++)
		ret = ov2659_write(client, regs[i].addr, regs[i].value);

	return ret;
}