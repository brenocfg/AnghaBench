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
typedef  int u16 ;
struct stv {TYPE_1__* base; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  adr; struct i2c_adapter* i2c; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int write_reg(struct stv *state, u16 reg, u8 val)
{
	struct i2c_adapter *adap = state->base->i2c;
	u8 data[3] = {reg >> 8, reg & 0xff, val};
	struct i2c_msg msg = {.addr = state->base->adr, .flags = 0,
			      .buf = data, .len = 3};

	if (i2c_transfer(adap, &msg, 1) != 1) {
		dev_warn(&adap->dev, "i2c write error ([%02x] %04x: %02x)\n",
			 state->base->adr, reg, val);
		return -EIO;
	}
	return 0;
}