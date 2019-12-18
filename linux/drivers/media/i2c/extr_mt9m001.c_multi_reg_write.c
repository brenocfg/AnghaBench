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
struct mt9m001_reg {int /*<<< orphan*/  data; int /*<<< orphan*/  reg; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multi_reg_write(struct i2c_client *client,
			   const struct mt9m001_reg *regs, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		int ret = reg_write(client, regs[i].reg, regs[i].data);

		if (ret)
			return ret;
	}

	return 0;
}