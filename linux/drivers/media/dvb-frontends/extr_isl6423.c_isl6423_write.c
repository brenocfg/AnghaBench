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
typedef  int u8 ;
struct isl6423_dev {TYPE_1__* config; struct i2c_adapter* i2c; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int isl6423_write(struct isl6423_dev *isl6423, u8 reg)
{
	struct i2c_adapter *i2c = isl6423->i2c;
	u8 addr			= isl6423->config->addr;
	int err = 0;

	struct i2c_msg msg = { .addr = addr, .flags = 0, .buf = &reg, .len = 1 };

	dprintk(FE_DEBUG, 1, "write reg %02X", reg);
	err = i2c_transfer(i2c, &msg, 1);
	if (err < 0)
		goto exit;
	return 0;

exit:
	dprintk(FE_ERROR, 1, "I/O error <%d>", err);
	return err;
}