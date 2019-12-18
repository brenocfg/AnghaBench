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
struct imx_i2c_struct {unsigned int i2csr; int /*<<< orphan*/  queue; TYPE_1__* hwdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned int i2sr_clr_opcode; } ;

/* Variables and functions */
 unsigned int I2SR_IIF ; 
 int /*<<< orphan*/  IMX_I2C_I2SR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int imx_i2c_read_reg (struct imx_i2c_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_i2c_write_reg (unsigned int,struct imx_i2c_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i2c_imx_isr(int irq, void *dev_id)
{
	struct imx_i2c_struct *i2c_imx = dev_id;
	unsigned int temp;

	temp = imx_i2c_read_reg(i2c_imx, IMX_I2C_I2SR);
	if (temp & I2SR_IIF) {
		/* save status register */
		i2c_imx->i2csr = temp;
		temp &= ~I2SR_IIF;
		temp |= (i2c_imx->hwdata->i2sr_clr_opcode & I2SR_IIF);
		imx_i2c_write_reg(temp, i2c_imx, IMX_I2C_I2SR);
		wake_up(&i2c_imx->queue);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}