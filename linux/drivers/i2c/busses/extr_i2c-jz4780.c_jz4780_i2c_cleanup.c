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
struct jz4780_i2c {TYPE_1__ adap; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4780_I2C_CINTR ; 
 int /*<<< orphan*/  JZ4780_I2C_CTRL ; 
 unsigned short JZ4780_I2C_CTRL_STPHLD ; 
 int /*<<< orphan*/  JZ4780_I2C_CTXABRT ; 
 unsigned short JZ4780_I2C_ENB_I2C ; 
 int /*<<< orphan*/  JZ4780_I2C_INTM ; 
 int /*<<< orphan*/  JZ4780_I2C_INTST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int jz4780_i2c_disable (struct jz4780_i2c*) ; 
 unsigned short jz4780_i2c_readw (struct jz4780_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (unsigned short) ; 

__attribute__((used)) static int jz4780_i2c_cleanup(struct jz4780_i2c *i2c)
{
	int ret;
	unsigned long flags;
	unsigned short tmp;

	spin_lock_irqsave(&i2c->lock, flags);

	/* can send stop now if need */
	tmp = jz4780_i2c_readw(i2c, JZ4780_I2C_CTRL);
	tmp &= ~JZ4780_I2C_CTRL_STPHLD;
	jz4780_i2c_writew(i2c, JZ4780_I2C_CTRL, tmp);

	/* disable all interrupts first */
	jz4780_i2c_writew(i2c, JZ4780_I2C_INTM, 0);

	/* then clear all interrupts */
	jz4780_i2c_readw(i2c, JZ4780_I2C_CTXABRT);
	jz4780_i2c_readw(i2c, JZ4780_I2C_CINTR);

	/* then disable the controller */
	tmp = jz4780_i2c_readw(i2c, JZ4780_I2C_CTRL);
	tmp &= ~JZ4780_I2C_ENB_I2C;
	jz4780_i2c_writew(i2c, JZ4780_I2C_CTRL, tmp);
	udelay(10);
	tmp |= JZ4780_I2C_ENB_I2C;
	jz4780_i2c_writew(i2c, JZ4780_I2C_CTRL, tmp);

	spin_unlock_irqrestore(&i2c->lock, flags);

	ret = jz4780_i2c_disable(i2c);
	if (ret)
		dev_err(&i2c->adap.dev,
			"unable to disable device during cleanup!\n");

	if (unlikely(jz4780_i2c_readw(i2c, JZ4780_I2C_INTM)
		     & jz4780_i2c_readw(i2c, JZ4780_I2C_INTST)))
		dev_err(&i2c->adap.dev,
			"device has interrupts after a complete cleanup!\n");

	return ret;
}