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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_read(struct i2c_adapter *adap,
		    u8 adr, u8 *msg, int len, u8 *answ, int alen)
{
	struct i2c_msg msgs[2] = { { .addr = adr, .flags = 0,
				     .buf = msg, .len = len},
				   { .addr = adr, .flags = I2C_M_RD,
				     .buf = answ, .len = alen } };
	if (i2c_transfer(adap, msgs, 2) != 2) {
		dev_err(&adap->dev, "i2c read error\n");
		return -EIO;
	}
	return 0;
}