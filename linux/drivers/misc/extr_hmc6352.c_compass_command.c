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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int compass_command(struct i2c_client *c, u8 cmd)
{
	int ret = i2c_master_send(c, &cmd, 1);
	if (ret < 0)
		dev_warn(&c->dev, "command '%c' failed.\n", cmd);
	return ret;
}