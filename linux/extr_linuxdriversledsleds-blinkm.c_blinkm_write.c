#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int nr_args; int /*<<< orphan*/  cmdbyte; } ;

/* Variables and functions */
 TYPE_1__* blinkm_cmds ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blinkm_write(struct i2c_client *client, int cmd, u8 *arg)
{
	int result;
	int i;
	int arglen = blinkm_cmds[cmd].nr_args;
	/* write out cmd to blinkm - always / default step */
	result = i2c_smbus_write_byte(client, blinkm_cmds[cmd].cmdbyte);
	if (result < 0)
		return result;
	/* no args to write out */
	if (arglen == 0)
		return 0;

	for (i = 0; i < arglen; i++) {
		/* repeat for arglen */
		result = i2c_smbus_write_byte(client, arg[i]);
		if (result < 0)
			return result;
	}
	return 0;
}