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
typedef  int uint32_t ;
struct mxs_i2c_dev {scalar_t__ dev_type; scalar_t__ regs; int /*<<< orphan*/  dev; } ;
struct i2c_msg {int flags; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENXIO ; 
 int I2C_M_RD ; 
 int MXS_CMD_I2C_READ ; 
 int MXS_CMD_I2C_SELECT ; 
 scalar_t__ MXS_I2C_CTRL0_CLR ; 
 int MXS_I2C_CTRL0_DIRECTION ; 
 int MXS_I2C_CTRL0_MASTER_MODE ; 
 int MXS_I2C_CTRL0_PIO_MODE ; 
 int MXS_I2C_CTRL0_POST_SEND_STOP ; 
 int MXS_I2C_CTRL0_PRE_SEND_START ; 
 int MXS_I2C_CTRL0_RETAIN_CLOCK ; 
 int MXS_I2C_CTRL0_XFER_COUNT (int) ; 
 scalar_t__ MXS_I2C_CTRL1_CLR ; 
 scalar_t__ MXS_I2C_CTRL1_SET ; 
 scalar_t__ MXS_I2C_DATA (struct mxs_i2c_dev*) ; 
 scalar_t__ MXS_I2C_DEBUG0_CLR (struct mxs_i2c_dev*) ; 
 int MXS_I2C_DEBUG0_DMAREQ ; 
 int MXS_I2C_IRQ_MASK ; 
 scalar_t__ MXS_I2C_STAT ; 
 int MXS_I2C_STAT_GOT_A_NAK ; 
 scalar_t__ MXS_I2C_V1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 struct mxs_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int mxs_i2c_pio_check_error_state (struct mxs_i2c_dev*) ; 
 int /*<<< orphan*/  mxs_i2c_pio_trigger_cmd (struct mxs_i2c_dev*,int) ; 
 int /*<<< orphan*/  mxs_i2c_pio_trigger_write_cmd (struct mxs_i2c_dev*,int,int) ; 
 int mxs_i2c_pio_wait_xfer_end (struct mxs_i2c_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_i2c_pio_setup_xfer(struct i2c_adapter *adap,
			struct i2c_msg *msg, uint32_t flags)
{
	struct mxs_i2c_dev *i2c = i2c_get_adapdata(adap);
	uint32_t addr_data = i2c_8bit_addr_from_msg(msg);
	uint32_t data = 0;
	int i, ret, xlen = 0, xmit = 0;
	uint32_t start;

	/* Mute IRQs coming from this block. */
	writel(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_CLR);

	/*
	 * MX23 idea:
	 * - Enable CTRL0::PIO_MODE (1 << 24)
	 * - Enable CTRL1::ACK_MODE (1 << 27)
	 *
	 * WARNING! The MX23 is broken in some way, even if it claims
	 * to support PIO, when we try to transfer any amount of data
	 * that is not aligned to 4 bytes, the DMA engine will have
	 * bits in DEBUG1::DMA_BYTES_ENABLES still set even after the
	 * transfer. This in turn will mess up the next transfer as
	 * the block it emit one byte write onto the bus terminated
	 * with a NAK+STOP. A possible workaround is to reset the IP
	 * block after every PIO transmission, which might just work.
	 *
	 * NOTE: The CTRL0::PIO_MODE description is important, since
	 * it outlines how the PIO mode is really supposed to work.
	 */
	if (msg->flags & I2C_M_RD) {
		/*
		 * PIO READ transfer:
		 *
		 * This transfer MUST be limited to 4 bytes maximum. It is not
		 * possible to transfer more than four bytes via PIO, since we
		 * can not in any way make sure we can read the data from the
		 * DATA register fast enough. Besides, the RX FIFO is only four
		 * bytes deep, thus we can only really read up to four bytes at
		 * time. Finally, there is no bit indicating us that new data
		 * arrived at the FIFO and can thus be fetched from the DATA
		 * register.
		 */
		BUG_ON(msg->len > 4);

		/* SELECT command. */
		mxs_i2c_pio_trigger_write_cmd(i2c, MXS_CMD_I2C_SELECT,
					      addr_data);

		ret = mxs_i2c_pio_wait_xfer_end(i2c);
		if (ret) {
			dev_dbg(i2c->dev,
				"PIO: Failed to send SELECT command!\n");
			goto cleanup;
		}

		/* READ command. */
		mxs_i2c_pio_trigger_cmd(i2c,
					MXS_CMD_I2C_READ | flags |
					MXS_I2C_CTRL0_XFER_COUNT(msg->len));

		ret = mxs_i2c_pio_wait_xfer_end(i2c);
		if (ret) {
			dev_dbg(i2c->dev,
				"PIO: Failed to send READ command!\n");
			goto cleanup;
		}

		data = readl(i2c->regs + MXS_I2C_DATA(i2c));
		for (i = 0; i < msg->len; i++) {
			msg->buf[i] = data & 0xff;
			data >>= 8;
		}
	} else {
		/*
		 * PIO WRITE transfer:
		 *
		 * The code below implements clock stretching to circumvent
		 * the possibility of kernel not being able to supply data
		 * fast enough. It is possible to transfer arbitrary amount
		 * of data using PIO write.
		 */

		/*
		 * The LSB of data buffer is the first byte blasted across
		 * the bus. Higher order bytes follow. Thus the following
		 * filling schematic.
		 */

		data = addr_data << 24;

		/* Start the transfer with START condition. */
		start = MXS_I2C_CTRL0_PRE_SEND_START;

		/* If the transfer is long, use clock stretching. */
		if (msg->len > 3)
			start |= MXS_I2C_CTRL0_RETAIN_CLOCK;

		for (i = 0; i < msg->len; i++) {
			data >>= 8;
			data |= (msg->buf[i] << 24);

			xmit = 0;

			/* This is the last transfer of the message. */
			if (i + 1 == msg->len) {
				/* Add optional STOP flag. */
				start |= flags;
				/* Remove RETAIN_CLOCK bit. */
				start &= ~MXS_I2C_CTRL0_RETAIN_CLOCK;
				xmit = 1;
			}

			/* Four bytes are ready in the "data" variable. */
			if ((i & 3) == 2)
				xmit = 1;

			/* Nothing interesting happened, continue stuffing. */
			if (!xmit)
				continue;

			/*
			 * Compute the size of the transfer and shift the
			 * data accordingly.
			 *
			 * i = (4k + 0) .... xlen = 2
			 * i = (4k + 1) .... xlen = 3
			 * i = (4k + 2) .... xlen = 4
			 * i = (4k + 3) .... xlen = 1
			 */

			if ((i % 4) == 3)
				xlen = 1;
			else
				xlen = (i % 4) + 2;

			data >>= (4 - xlen) * 8;

			dev_dbg(i2c->dev,
				"PIO: len=%i pos=%i total=%i [W%s%s%s]\n",
				xlen, i, msg->len,
				start & MXS_I2C_CTRL0_PRE_SEND_START ? "S" : "",
				start & MXS_I2C_CTRL0_POST_SEND_STOP ? "E" : "",
				start & MXS_I2C_CTRL0_RETAIN_CLOCK ? "C" : "");

			writel(MXS_I2C_DEBUG0_DMAREQ,
			       i2c->regs + MXS_I2C_DEBUG0_CLR(i2c));

			mxs_i2c_pio_trigger_write_cmd(i2c,
				start | MXS_I2C_CTRL0_MASTER_MODE |
				MXS_I2C_CTRL0_DIRECTION |
				MXS_I2C_CTRL0_XFER_COUNT(xlen), data);

			/* The START condition is sent only once. */
			start &= ~MXS_I2C_CTRL0_PRE_SEND_START;

			/* Wait for the end of the transfer. */
			ret = mxs_i2c_pio_wait_xfer_end(i2c);
			if (ret) {
				dev_dbg(i2c->dev,
					"PIO: Failed to finish WRITE cmd!\n");
				break;
			}

			/* Check NAK here. */
			ret = readl(i2c->regs + MXS_I2C_STAT) &
				    MXS_I2C_STAT_GOT_A_NAK;
			if (ret) {
				ret = -ENXIO;
				goto cleanup;
			}
		}
	}

	/* make sure we capture any occurred error into cmd_err */
	ret = mxs_i2c_pio_check_error_state(i2c);

cleanup:
	/* Clear any dangling IRQs and re-enable interrupts. */
	writel(MXS_I2C_IRQ_MASK, i2c->regs + MXS_I2C_CTRL1_CLR);
	writel(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_SET);

	/* Clear the PIO_MODE on i.MX23 */
	if (i2c->dev_type == MXS_I2C_V1)
		writel(MXS_I2C_CTRL0_PIO_MODE, i2c->regs + MXS_I2C_CTRL0_CLR);

	return ret;
}