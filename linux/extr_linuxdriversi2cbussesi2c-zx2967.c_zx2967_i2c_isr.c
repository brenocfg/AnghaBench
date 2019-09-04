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
typedef  int u32 ;
struct zx2967_i2c {int /*<<< orphan*/  complete; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENXIO ; 
 int I2C_INT_MASK ; 
 int I2C_SR_EDATA ; 
 int I2C_SR_EDEVICE ; 
 int I2C_TRANS_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_STAT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zx2967_i2c_isr_clr (struct zx2967_i2c*) ; 
 int zx2967_i2c_readl (struct zx2967_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t zx2967_i2c_isr(int irq, void *dev_id)
{
	u32 status;
	struct zx2967_i2c *i2c = (struct zx2967_i2c *)dev_id;

	status = zx2967_i2c_readl(i2c, REG_STAT) & I2C_INT_MASK;
	zx2967_i2c_isr_clr(i2c);

	if (status & I2C_SR_EDEVICE)
		i2c->error = -ENXIO;
	else if (status & I2C_SR_EDATA)
		i2c->error = -EIO;
	else if (status & I2C_TRANS_DONE)
		i2c->error = 0;
	else
		goto done;

	complete(&i2c->complete);
done:
	return IRQ_HANDLED;
}