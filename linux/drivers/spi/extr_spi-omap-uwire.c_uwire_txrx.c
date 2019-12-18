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
typedef  int u16 ;
struct spi_transfer {unsigned int len; unsigned int bits_per_word; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_device {int chip_select; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CSRB ; 
 int CS_CMD ; 
 int EIO ; 
 int RDRB ; 
 int START ; 
 int /*<<< orphan*/  UWIRE_CSR ; 
 int /*<<< orphan*/  UWIRE_RDR ; 
 int /*<<< orphan*/  UWIRE_TDR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int uwire_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwire_write_reg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_uwire_csr_flag (int,int,int) ; 

__attribute__((used)) static int uwire_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	unsigned	len = t->len;
	unsigned	bits = t->bits_per_word;
	unsigned	bytes;
	u16		val, w;
	int		status = 0;

	if (!t->tx_buf && !t->rx_buf)
		return 0;

	w = spi->chip_select << 10;
	w |= CS_CMD;

	if (t->tx_buf) {
		const u8	*buf = t->tx_buf;

		/* NOTE:  DMA could be used for TX transfers */

		/* write one or two bytes at a time */
		while (len >= 1) {
			/* tx bit 15 is first sent; we byteswap multibyte words
			 * (msb-first) on the way out from memory.
			 */
			val = *buf++;
			if (bits > 8) {
				bytes = 2;
				val |= *buf++ << 8;
			} else
				bytes = 1;
			val <<= 16 - bits;

#ifdef	VERBOSE
			pr_debug("%s: write-%d =%04x\n",
					dev_name(&spi->dev), bits, val);
#endif
			if (wait_uwire_csr_flag(CSRB, 0, 0))
				goto eio;

			uwire_write_reg(UWIRE_TDR, val);

			/* start write */
			val = START | w | (bits << 5);

			uwire_write_reg(UWIRE_CSR, val);
			len -= bytes;

			/* Wait till write actually starts.
			 * This is needed with MPU clock 60+ MHz.
			 * REVISIT: we may not have time to catch it...
			 */
			if (wait_uwire_csr_flag(CSRB, CSRB, 1))
				goto eio;

			status += bytes;
		}

		/* REVISIT:  save this for later to get more i/o overlap */
		if (wait_uwire_csr_flag(CSRB, 0, 0))
			goto eio;

	} else if (t->rx_buf) {
		u8		*buf = t->rx_buf;

		/* read one or two bytes at a time */
		while (len) {
			if (bits > 8) {
				bytes = 2;
			} else
				bytes = 1;

			/* start read */
			val = START | w | (bits << 0);
			uwire_write_reg(UWIRE_CSR, val);
			len -= bytes;

			/* Wait till read actually starts */
			(void) wait_uwire_csr_flag(CSRB, CSRB, 1);

			if (wait_uwire_csr_flag(RDRB | CSRB,
						RDRB, 0))
				goto eio;

			/* rx bit 0 is last received; multibyte words will
			 * be properly byteswapped on the way to memory.
			 */
			val = uwire_read_reg(UWIRE_RDR);
			val &= (1 << bits) - 1;
			*buf++ = (u8) val;
			if (bytes == 2)
				*buf++ = val >> 8;
			status += bytes;
#ifdef	VERBOSE
			pr_debug("%s: read-%d =%04x\n",
					dev_name(&spi->dev), bits, val);
#endif

		}
	}
	return status;
eio:
	return -EIO;
}