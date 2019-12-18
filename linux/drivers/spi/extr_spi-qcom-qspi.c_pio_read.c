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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {unsigned int rem_bytes; int* rx_buf; } ;
struct qcom_qspi {TYPE_1__ xfer; scalar_t__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int FIFO_RDY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int QSPI_BYTES_PER_WORD ; 
 scalar_t__ RD_FIFO ; 
 scalar_t__ RD_FIFO_STATUS ; 
 int WR_CNTS_MSK ; 
 int WR_CNTS_SHFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,int*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t pio_read(struct qcom_qspi *ctrl)
{
	u32 rd_fifo_status;
	u32 rd_fifo;
	unsigned int wr_cnts;
	unsigned int bytes_to_read;
	unsigned int words_to_read;
	u32 *word_buf;
	u8 *byte_buf;
	int i;

	rd_fifo_status = readl(ctrl->base + RD_FIFO_STATUS);

	if (!(rd_fifo_status & FIFO_RDY)) {
		dev_dbg(ctrl->dev, "Spurious IRQ %#x\n", rd_fifo_status);
		return IRQ_NONE;
	}

	wr_cnts = (rd_fifo_status & WR_CNTS_MSK) >> WR_CNTS_SHFT;
	wr_cnts = min(wr_cnts, ctrl->xfer.rem_bytes);

	words_to_read = wr_cnts / QSPI_BYTES_PER_WORD;
	bytes_to_read = wr_cnts % QSPI_BYTES_PER_WORD;

	if (words_to_read) {
		word_buf = ctrl->xfer.rx_buf;
		ctrl->xfer.rem_bytes -= words_to_read * QSPI_BYTES_PER_WORD;
		ioread32_rep(ctrl->base + RD_FIFO, word_buf, words_to_read);
		ctrl->xfer.rx_buf = word_buf + words_to_read;
	}

	if (bytes_to_read) {
		byte_buf = ctrl->xfer.rx_buf;
		rd_fifo = readl(ctrl->base + RD_FIFO);
		ctrl->xfer.rem_bytes -= bytes_to_read;
		for (i = 0; i < bytes_to_read; i++)
			*byte_buf++ = rd_fifo >> (i * BITS_PER_BYTE);
		ctrl->xfer.rx_buf = byte_buf;
	}

	return IRQ_HANDLED;
}