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
struct cdns_i2c {unsigned int recv_count; unsigned int curr_recv_count; TYPE_1__* p_msg; scalar_t__ bus_hold_flag; int /*<<< orphan*/  p_recv_buf; } ;
struct TYPE_2__ {unsigned int len; int flags; unsigned int addr; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned int CDNS_I2C_ADDR_MASK ; 
 int /*<<< orphan*/  CDNS_I2C_ADDR_OFFSET ; 
 unsigned int CDNS_I2C_CR_CLR_FIFO ; 
 unsigned int CDNS_I2C_CR_HOLD ; 
 int /*<<< orphan*/  CDNS_I2C_CR_OFFSET ; 
 unsigned int CDNS_I2C_CR_RW ; 
 unsigned int CDNS_I2C_ENABLED_INTR_MASK ; 
 scalar_t__ CDNS_I2C_FIFO_DEPTH ; 
 int /*<<< orphan*/  CDNS_I2C_IER_OFFSET ; 
 int /*<<< orphan*/  CDNS_I2C_ISR_OFFSET ; 
 unsigned int CDNS_I2C_TRANSFER_SIZE ; 
 int /*<<< orphan*/  CDNS_I2C_XFER_SIZE_OFFSET ; 
 int I2C_M_RECV_LEN ; 
 unsigned int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  cdns_i2c_clear_bus_hold (struct cdns_i2c*) ; 
 unsigned int cdns_i2c_readreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_i2c_writereg (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns_i2c_mrecv(struct cdns_i2c *id)
{
	unsigned int ctrl_reg;
	unsigned int isr_status;

	id->p_recv_buf = id->p_msg->buf;
	id->recv_count = id->p_msg->len;

	/* Put the controller in master receive mode and clear the FIFO */
	ctrl_reg = cdns_i2c_readreg(CDNS_I2C_CR_OFFSET);
	ctrl_reg |= CDNS_I2C_CR_RW | CDNS_I2C_CR_CLR_FIFO;

	if (id->p_msg->flags & I2C_M_RECV_LEN)
		id->recv_count = I2C_SMBUS_BLOCK_MAX + 1;

	id->curr_recv_count = id->recv_count;

	/*
	 * Check for the message size against FIFO depth and set the
	 * 'hold bus' bit if it is greater than FIFO depth.
	 */
	if ((id->recv_count > CDNS_I2C_FIFO_DEPTH)  || id->bus_hold_flag)
		ctrl_reg |= CDNS_I2C_CR_HOLD;
	else
		ctrl_reg = ctrl_reg & ~CDNS_I2C_CR_HOLD;

	cdns_i2c_writereg(ctrl_reg, CDNS_I2C_CR_OFFSET);

	/* Clear the interrupts in interrupt status register */
	isr_status = cdns_i2c_readreg(CDNS_I2C_ISR_OFFSET);
	cdns_i2c_writereg(isr_status, CDNS_I2C_ISR_OFFSET);

	/*
	 * The no. of bytes to receive is checked against the limit of
	 * max transfer size. Set transfer size register with no of bytes
	 * receive if it is less than transfer size and transfer size if
	 * it is more. Enable the interrupts.
	 */
	if (id->recv_count > CDNS_I2C_TRANSFER_SIZE) {
		cdns_i2c_writereg(CDNS_I2C_TRANSFER_SIZE,
				  CDNS_I2C_XFER_SIZE_OFFSET);
		id->curr_recv_count = CDNS_I2C_TRANSFER_SIZE;
	} else {
		cdns_i2c_writereg(id->recv_count, CDNS_I2C_XFER_SIZE_OFFSET);
	}

	/* Set the slave address in address register - triggers operation */
	cdns_i2c_writereg(id->p_msg->addr & CDNS_I2C_ADDR_MASK,
						CDNS_I2C_ADDR_OFFSET);
	/* Clear the bus hold flag if bytes to receive is less than FIFO size */
	if (!id->bus_hold_flag &&
		((id->p_msg->flags & I2C_M_RECV_LEN) != I2C_M_RECV_LEN) &&
		(id->recv_count <= CDNS_I2C_FIFO_DEPTH))
			cdns_i2c_clear_bus_hold(id);
	cdns_i2c_writereg(CDNS_I2C_ENABLED_INTR_MASK, CDNS_I2C_IER_OFFSET);
}