#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ov9640_reg_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ov9640_regs_dflt ; 

__attribute__((used)) static int ov9640_prog_dflt(struct i2c_client *client)
{
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(ov9640_regs_dflt); i++) {
		ret = ov9640_reg_write(client, ov9640_regs_dflt[i].reg,
				       ov9640_regs_dflt[i].val);
		if (ret)
			return ret;
	}

	/* wait for the changes to actually happen, 140ms are not enough yet */
	msleep(150);

	return 0;
}