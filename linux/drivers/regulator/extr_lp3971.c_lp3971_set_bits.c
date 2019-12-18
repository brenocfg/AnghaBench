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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct lp3971 {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int lp3971_i2c_read (int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 int lp3971_i2c_write (int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp3971_set_bits(struct lp3971 *lp3971, u8 reg, u16 mask, u16 val)
{
	u16 tmp;
	int ret;

	mutex_lock(&lp3971->io_lock);

	ret = lp3971_i2c_read(lp3971->i2c, reg, 1, &tmp);
	if (ret == 0) {
		tmp = (tmp & ~mask) | val;
		ret = lp3971_i2c_write(lp3971->i2c, reg, 1, &tmp);
		dev_dbg(lp3971->dev, "reg write 0x%02x -> 0x%02x\n", (int)reg,
			(unsigned)val&0xff);
	}
	mutex_unlock(&lp3971->io_lock);

	return ret;
}