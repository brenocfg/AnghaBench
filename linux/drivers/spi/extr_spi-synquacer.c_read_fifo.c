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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct synquacer_spi {int rx_words; int bpw; int* rx_buf; scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int SYNQUACER_HSSPI_DMSTATUS_RX_DATA_MASK ; 
 int SYNQUACER_HSSPI_DMSTATUS_RX_DATA_SHIFT ; 
 scalar_t__ SYNQUACER_HSSPI_REG_DMSTATUS ; 
 scalar_t__ SYNQUACER_HSSPI_REG_RX_FIFO ; 
 int /*<<< orphan*/  ioread16_rep (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  ioread8_rep (scalar_t__,int*,int) ; 
 int min (int,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int read_fifo(struct synquacer_spi *sspi)
{
	u32 len = readl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTATUS);

	len = (len >> SYNQUACER_HSSPI_DMSTATUS_RX_DATA_SHIFT) &
	       SYNQUACER_HSSPI_DMSTATUS_RX_DATA_MASK;
	len = min(len, sspi->rx_words);

	switch (sspi->bpw) {
	case 8: {
		u8 *buf = sspi->rx_buf;

		ioread8_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			    buf, len);
		sspi->rx_buf = buf + len;
		break;
	}
	case 16: {
		u16 *buf = sspi->rx_buf;

		ioread16_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			     buf, len);
		sspi->rx_buf = buf + len;
		break;
	}
	case 24:
		/* fallthrough, should use 32-bits access */
	case 32: {
		u32 *buf = sspi->rx_buf;

		ioread32_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			     buf, len);
		sspi->rx_buf = buf + len;
		break;
	}
	default:
		return -EINVAL;
	}

	sspi->rx_words -= len;
	return 0;
}