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
struct i2c_cmd_arg {unsigned int cmd; void* arg; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct i2c_cmd_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_cmd ; 

void i2c_clients_command(struct i2c_adapter *adap, unsigned int cmd, void *arg)
{
	struct i2c_cmd_arg	cmd_arg;

	cmd_arg.cmd = cmd;
	cmd_arg.arg = arg;
	device_for_each_child(&adap->dev, &cmd_arg, i2c_cmd);
}