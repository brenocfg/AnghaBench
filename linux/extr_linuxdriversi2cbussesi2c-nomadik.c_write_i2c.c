#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  slave_adr; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;
struct nmk_i2c_dev {TYPE_4__ cli; TYPE_3__* adev; TYPE_2__ adap; int /*<<< orphan*/  xfer_complete; scalar_t__ virtbase; TYPE_1__* vendor; scalar_t__ stop; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_mtdws; } ;

/* Variables and functions */
 int DEFAULT_I2C_REG_CR ; 
 int ETIMEDOUT ; 
 int I2C_CLEAR_ALL_INTS ; 
 scalar_t__ I2C_CR ; 
 int /*<<< orphan*/  I2C_CR_PE ; 
 scalar_t__ I2C_IMSCR ; 
 int I2C_IT_BERR ; 
 int I2C_IT_MAL ; 
 int I2C_IT_MTD ; 
 int I2C_IT_MTDWS ; 
 int I2C_IT_TXFNE ; 
 int I2C_IT_TXFOVR ; 
 scalar_t__ I2C_MCR ; 
 int IRQ_MASK (int) ; 
 int /*<<< orphan*/  MAX_I2C_FIFO_THRESHOLD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_tx_fifo (struct nmk_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int load_i2c_mcr_reg (struct nmk_i2c_dev*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int write_i2c(struct nmk_i2c_dev *dev, u16 flags)
{
	u32 status = 0;
	u32 mcr, irq_mask;
	unsigned long timeout;

	mcr = load_i2c_mcr_reg(dev, flags);

	writel(mcr, dev->virtbase + I2C_MCR);

	/* load the current CR value */
	writel(readl(dev->virtbase + I2C_CR) | DEFAULT_I2C_REG_CR,
			dev->virtbase + I2C_CR);

	/* enable the controller */
	i2c_set_bit(dev->virtbase + I2C_CR , I2C_CR_PE);

	init_completion(&dev->xfer_complete);

	/* enable interrupts by settings the masks */
	irq_mask = (I2C_IT_TXFOVR | I2C_IT_MAL | I2C_IT_BERR);

	/* Fill the TX FIFO with transmit data */
	fill_tx_fifo(dev, MAX_I2C_FIFO_THRESHOLD);

	if (dev->cli.count != 0)
		irq_mask |= I2C_IT_TXFNE;

	/*
	 * check if we want to transfer a single or multiple bytes, if so
	 * set the MTDWS bit (Master Transaction Done Without Stop)
	 * to start repeated start operation
	 */
	if (dev->stop || !dev->vendor->has_mtdws)
		irq_mask |= I2C_IT_MTD;
	else
		irq_mask |= I2C_IT_MTDWS;

	irq_mask = I2C_CLEAR_ALL_INTS & IRQ_MASK(irq_mask);

	writel(readl(dev->virtbase + I2C_IMSCR) | irq_mask,
			dev->virtbase + I2C_IMSCR);

	timeout = wait_for_completion_timeout(
		&dev->xfer_complete, dev->adap.timeout);

	if (timeout == 0) {
		/* Controller timed out */
		dev_err(&dev->adev->dev, "write to slave 0x%x timed out\n",
				dev->cli.slave_adr);
		status = -ETIMEDOUT;
	}

	return status;
}