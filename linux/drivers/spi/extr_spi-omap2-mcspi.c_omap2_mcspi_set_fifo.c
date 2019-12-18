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
struct spi_transfer {int len; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {struct omap2_mcspi_cs* controller_state; struct spi_master* master; } ;
struct omap2_mcspi_cs {int /*<<< orphan*/  word_len; } ;
struct omap2_mcspi {int fifo_depth; } ;

/* Variables and functions */
 int OMAP2_MCSPI_CHCONF_FFER ; 
 int OMAP2_MCSPI_CHCONF_FFET ; 
 int OMAP2_MCSPI_MAX_FIFODEPTH ; 
 unsigned int OMAP2_MCSPI_MAX_FIFOWCNT ; 
 int /*<<< orphan*/  OMAP2_MCSPI_XFERLEVEL ; 
 int mcspi_bytes_per_word (int /*<<< orphan*/ ) ; 
 int mcspi_cached_chconf0 (struct spi_device const*) ; 
 int /*<<< orphan*/  mcspi_write_chconf0 (struct spi_device const*,int) ; 
 int /*<<< orphan*/  mcspi_write_reg (struct spi_master*,int /*<<< orphan*/ ,int) ; 
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void omap2_mcspi_set_fifo(const struct spi_device *spi,
				struct spi_transfer *t, int enable)
{
	struct spi_master *master = spi->master;
	struct omap2_mcspi_cs *cs = spi->controller_state;
	struct omap2_mcspi *mcspi;
	unsigned int wcnt;
	int max_fifo_depth, bytes_per_word;
	u32 chconf, xferlevel;

	mcspi = spi_master_get_devdata(master);

	chconf = mcspi_cached_chconf0(spi);
	if (enable) {
		bytes_per_word = mcspi_bytes_per_word(cs->word_len);
		if (t->len % bytes_per_word != 0)
			goto disable_fifo;

		if (t->rx_buf != NULL && t->tx_buf != NULL)
			max_fifo_depth = OMAP2_MCSPI_MAX_FIFODEPTH / 2;
		else
			max_fifo_depth = OMAP2_MCSPI_MAX_FIFODEPTH;

		wcnt = t->len / bytes_per_word;
		if (wcnt > OMAP2_MCSPI_MAX_FIFOWCNT)
			goto disable_fifo;

		xferlevel = wcnt << 16;
		if (t->rx_buf != NULL) {
			chconf |= OMAP2_MCSPI_CHCONF_FFER;
			xferlevel |= (bytes_per_word - 1) << 8;
		}

		if (t->tx_buf != NULL) {
			chconf |= OMAP2_MCSPI_CHCONF_FFET;
			xferlevel |= bytes_per_word - 1;
		}

		mcspi_write_reg(master, OMAP2_MCSPI_XFERLEVEL, xferlevel);
		mcspi_write_chconf0(spi, chconf);
		mcspi->fifo_depth = max_fifo_depth;

		return;
	}

disable_fifo:
	if (t->rx_buf != NULL)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFER;

	if (t->tx_buf != NULL)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFET;

	mcspi_write_chconf0(spi, chconf);
	mcspi->fifo_depth = 0;
}