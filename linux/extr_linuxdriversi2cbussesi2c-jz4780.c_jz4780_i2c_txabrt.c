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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct jz4780_i2c {size_t cmd; TYPE_1__ adap; int /*<<< orphan*/ * data_buf; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  JZ4780_I2C_TAR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,...) ; 
 int /*<<< orphan*/ * jz4780_i2c_abrt_src ; 
 int /*<<< orphan*/  jz4780_i2c_readw (struct jz4780_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4780_i2c_txabrt(struct jz4780_i2c *i2c, int src)
{
	int i;

	dev_err(&i2c->adap.dev, "txabrt: 0x%08x\n", src);
	dev_err(&i2c->adap.dev, "device addr=%x\n",
		jz4780_i2c_readw(i2c, JZ4780_I2C_TAR));
	dev_err(&i2c->adap.dev, "send cmd count:%d  %d\n",
		i2c->cmd, i2c->cmd_buf[i2c->cmd]);
	dev_err(&i2c->adap.dev, "receive data count:%d  %d\n",
		i2c->cmd, i2c->data_buf[i2c->cmd]);

	for (i = 0; i < 16; i++) {
		if (src & BIT(i))
			dev_dbg(&i2c->adap.dev, "I2C TXABRT[%d]=%s\n",
				i, jz4780_i2c_abrt_src[i]);
	}
}