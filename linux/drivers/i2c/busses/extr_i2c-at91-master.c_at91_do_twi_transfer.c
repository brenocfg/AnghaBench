#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;
struct at91_twi_dev {int buf_len; unsigned int transfer_status; int /*<<< orphan*/  dev; scalar_t__ fifo_size; scalar_t__ recv_len_abort; TYPE_3__ adapter; int /*<<< orphan*/  cmd_complete; scalar_t__ use_dma; TYPE_2__* msg; int /*<<< orphan*/  use_alt_cmd; TYPE_1__* pdata; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int has_unre_flag; int has_alt_cmd; } ;

/* Variables and functions */
 int AT91_I2C_DMA_THRESHOLD ; 
 int /*<<< orphan*/  AT91_TWI_CR ; 
 int /*<<< orphan*/  AT91_TWI_FMR ; 
 unsigned int AT91_TWI_FMR_RXRDYM (int /*<<< orphan*/ ) ; 
 unsigned int AT91_TWI_FMR_RXRDYM_MASK ; 
 unsigned int AT91_TWI_FMR_TXRDYM (int /*<<< orphan*/ ) ; 
 unsigned int AT91_TWI_FMR_TXRDYM_MASK ; 
 int /*<<< orphan*/  AT91_TWI_IER ; 
 int AT91_TWI_LOCK ; 
 int AT91_TWI_LOCKCLR ; 
 int AT91_TWI_NACK ; 
 int /*<<< orphan*/  AT91_TWI_ONE_DATA ; 
 int AT91_TWI_OVRE ; 
 int AT91_TWI_QUICK ; 
 int AT91_TWI_RHRCLR ; 
 int AT91_TWI_RXRDY ; 
 int /*<<< orphan*/  AT91_TWI_SR ; 
 unsigned int AT91_TWI_START ; 
 unsigned int AT91_TWI_STOP ; 
 int AT91_TWI_THRCLR ; 
 int AT91_TWI_TXCOMP ; 
 int AT91_TWI_TXRDY ; 
 int AT91_TWI_UNRE ; 
 int EIO ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 int /*<<< orphan*/  at91_init_twi_bus (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_dma_cleanup (struct at91_twi_dev*) ; 
 unsigned int at91_twi_read (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_twi_read_data_dma (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  at91_twi_write_data_dma (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_write_next_byte (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_do_twi_transfer(struct at91_twi_dev *dev)
{
	int ret;
	unsigned long time_left;
	bool has_unre_flag = dev->pdata->has_unre_flag;
	bool has_alt_cmd = dev->pdata->has_alt_cmd;

	/*
	 * WARNING: the TXCOMP bit in the Status Register is NOT a clear on
	 * read flag but shows the state of the transmission at the time the
	 * Status Register is read. According to the programmer datasheet,
	 * TXCOMP is set when both holding register and internal shifter are
	 * empty and STOP condition has been sent.
	 * Consequently, we should enable NACK interrupt rather than TXCOMP to
	 * detect transmission failure.
	 * Indeed let's take the case of an i2c write command using DMA.
	 * Whenever the slave doesn't acknowledge a byte, the LOCK, NACK and
	 * TXCOMP bits are set together into the Status Register.
	 * LOCK is a clear on write bit, which is set to prevent the DMA
	 * controller from sending new data on the i2c bus after a NACK
	 * condition has happened. Once locked, this i2c peripheral stops
	 * triggering the DMA controller for new data but it is more than
	 * likely that a new DMA transaction is already in progress, writing
	 * into the Transmit Holding Register. Since the peripheral is locked,
	 * these new data won't be sent to the i2c bus but they will remain
	 * into the Transmit Holding Register, so TXCOMP bit is cleared.
	 * Then when the interrupt handler is called, the Status Register is
	 * read: the TXCOMP bit is clear but NACK bit is still set. The driver
	 * manage the error properly, without waiting for timeout.
	 * This case can be reproduced easyly when writing into an at24 eeprom.
	 *
	 * Besides, the TXCOMP bit is already set before the i2c transaction
	 * has been started. For read transactions, this bit is cleared when
	 * writing the START bit into the Control Register. So the
	 * corresponding interrupt can safely be enabled just after.
	 * However for write transactions managed by the CPU, we first write
	 * into THR, so TXCOMP is cleared. Then we can safely enable TXCOMP
	 * interrupt. If TXCOMP interrupt were enabled before writing into THR,
	 * the interrupt handler would be called immediately and the i2c command
	 * would be reported as completed.
	 * Also when a write transaction is managed by the DMA controller,
	 * enabling the TXCOMP interrupt in this function may lead to a race
	 * condition since we don't know whether the TXCOMP interrupt is enabled
	 * before or after the DMA has started to write into THR. So the TXCOMP
	 * interrupt is enabled later by at91_twi_write_data_dma_callback().
	 * Immediately after in that DMA callback, if the alternative command
	 * mode is not used, we still need to send the STOP condition manually
	 * writing the corresponding bit into the Control Register.
	 */

	dev_dbg(dev->dev, "transfer: %s %zu bytes.\n",
		(dev->msg->flags & I2C_M_RD) ? "read" : "write", dev->buf_len);

	reinit_completion(&dev->cmd_complete);
	dev->transfer_status = 0;

	/* Clear pending interrupts, such as NACK. */
	at91_twi_read(dev, AT91_TWI_SR);

	if (dev->fifo_size) {
		unsigned fifo_mr = at91_twi_read(dev, AT91_TWI_FMR);

		/* Reset FIFO mode register */
		fifo_mr &= ~(AT91_TWI_FMR_TXRDYM_MASK |
			     AT91_TWI_FMR_RXRDYM_MASK);
		fifo_mr |= AT91_TWI_FMR_TXRDYM(AT91_TWI_ONE_DATA);
		fifo_mr |= AT91_TWI_FMR_RXRDYM(AT91_TWI_ONE_DATA);
		at91_twi_write(dev, AT91_TWI_FMR, fifo_mr);

		/* Flush FIFOs */
		at91_twi_write(dev, AT91_TWI_CR,
			       AT91_TWI_THRCLR | AT91_TWI_RHRCLR);
	}

	if (!dev->buf_len) {
		at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_QUICK);
		at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_TXCOMP);
	} else if (dev->msg->flags & I2C_M_RD) {
		unsigned start_flags = AT91_TWI_START;

		/* if only one byte is to be read, immediately stop transfer */
		if (!dev->use_alt_cmd && dev->buf_len <= 1 &&
		    !(dev->msg->flags & I2C_M_RECV_LEN))
			start_flags |= AT91_TWI_STOP;
		at91_twi_write(dev, AT91_TWI_CR, start_flags);
		/*
		 * When using dma without alternative command mode, the last
		 * byte has to be read manually in order to not send the stop
		 * command too late and then to receive extra data.
		 * In practice, there are some issues if you use the dma to
		 * read n-1 bytes because of latency.
		 * Reading n-2 bytes with dma and the two last ones manually
		 * seems to be the best solution.
		 */
		if (dev->use_dma && (dev->buf_len > AT91_I2C_DMA_THRESHOLD)) {
			at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_NACK);
			at91_twi_read_data_dma(dev);
		} else {
			at91_twi_write(dev, AT91_TWI_IER,
				       AT91_TWI_TXCOMP |
				       AT91_TWI_NACK |
				       AT91_TWI_RXRDY);
		}
	} else {
		if (dev->use_dma && (dev->buf_len > AT91_I2C_DMA_THRESHOLD)) {
			at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_NACK);
			at91_twi_write_data_dma(dev);
		} else {
			at91_twi_write_next_byte(dev);
			at91_twi_write(dev, AT91_TWI_IER,
				       AT91_TWI_TXCOMP | AT91_TWI_NACK |
				       (dev->buf_len ? AT91_TWI_TXRDY : 0));
		}
	}

	time_left = wait_for_completion_timeout(&dev->cmd_complete,
					      dev->adapter.timeout);
	if (time_left == 0) {
		dev->transfer_status |= at91_twi_read(dev, AT91_TWI_SR);
		dev_err(dev->dev, "controller timed out\n");
		at91_init_twi_bus(dev);
		ret = -ETIMEDOUT;
		goto error;
	}
	if (dev->transfer_status & AT91_TWI_NACK) {
		dev_dbg(dev->dev, "received nack\n");
		ret = -EREMOTEIO;
		goto error;
	}
	if (dev->transfer_status & AT91_TWI_OVRE) {
		dev_err(dev->dev, "overrun while reading\n");
		ret = -EIO;
		goto error;
	}
	if (has_unre_flag && dev->transfer_status & AT91_TWI_UNRE) {
		dev_err(dev->dev, "underrun while writing\n");
		ret = -EIO;
		goto error;
	}
	if ((has_alt_cmd || dev->fifo_size) &&
	    (dev->transfer_status & AT91_TWI_LOCK)) {
		dev_err(dev->dev, "tx locked\n");
		ret = -EIO;
		goto error;
	}
	if (dev->recv_len_abort) {
		dev_err(dev->dev, "invalid smbus block length recvd\n");
		ret = -EPROTO;
		goto error;
	}

	dev_dbg(dev->dev, "transfer complete\n");

	return 0;

error:
	/* first stop DMA transfer if still in progress */
	at91_twi_dma_cleanup(dev);
	/* then flush THR/FIFO and unlock TX if locked */
	if ((has_alt_cmd || dev->fifo_size) &&
	    (dev->transfer_status & AT91_TWI_LOCK)) {
		dev_dbg(dev->dev, "unlock tx\n");
		at91_twi_write(dev, AT91_TWI_CR,
			       AT91_TWI_THRCLR | AT91_TWI_LOCKCLR);
	}
	return ret;
}