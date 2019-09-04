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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct spi_nor {int dummy; } ;
struct fsl_qspi {scalar_t__ iobase; int /*<<< orphan*/  chip_base_addr; int /*<<< orphan*/  dev; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 scalar_t__ QUADSPI_MCR ; 
 int QUADSPI_MCR_CLR_TXF_MASK ; 
 scalar_t__ QUADSPI_TBDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int fsl_qspi_endian_xchg (struct fsl_qspi*,int) ; 
 int fsl_qspi_runcmd (struct fsl_qspi*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ needs_fill_txfifo (struct fsl_qspi*) ; 
 int qspi_readl (struct fsl_qspi*,scalar_t__) ; 
 int /*<<< orphan*/  qspi_writel (struct fsl_qspi*,int,scalar_t__) ; 

__attribute__((used)) static ssize_t fsl_qspi_nor_write(struct fsl_qspi *q, struct spi_nor *nor,
				u8 opcode, unsigned int to, u32 *txbuf,
				unsigned count)
{
	int ret, i, j;
	u32 tmp;

	dev_dbg(q->dev, "to 0x%.8x:0x%.8x, len : %d\n",
		q->chip_base_addr, to, count);

	/* clear the TX FIFO. */
	tmp = qspi_readl(q, q->iobase + QUADSPI_MCR);
	qspi_writel(q, tmp | QUADSPI_MCR_CLR_TXF_MASK, q->iobase + QUADSPI_MCR);

	/* fill the TX data to the FIFO */
	for (j = 0, i = ((count + 3) / 4); j < i; j++) {
		tmp = fsl_qspi_endian_xchg(q, *txbuf);
		qspi_writel(q, tmp, q->iobase + QUADSPI_TBDR);
		txbuf++;
	}

	/* fill the TXFIFO upto 16 bytes for i.MX7d */
	if (needs_fill_txfifo(q))
		for (; i < 4; i++)
			qspi_writel(q, tmp, q->iobase + QUADSPI_TBDR);

	/* Trigger it */
	ret = fsl_qspi_runcmd(q, opcode, to, count);

	if (ret == 0)
		return count;

	return ret;
}