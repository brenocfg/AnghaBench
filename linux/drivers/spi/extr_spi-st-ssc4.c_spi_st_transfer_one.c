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
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_st {int bytes_per_word; int words_remaining; scalar_t__ base; int /*<<< orphan*/  done; int /*<<< orphan*/  rx_ptr; int /*<<< orphan*/  tx_ptr; } ;
struct spi_master {int dummy; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ SSC_CTL ; 
 scalar_t__ SSC_IEN ; 
 int SSC_IEN_TEEN ; 
 scalar_t__ SSC_RBUF ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (int /*<<< orphan*/ ) ; 
 struct spi_st* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  ssc_write_tx_fifo (struct spi_st*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spi_st_transfer_one(struct spi_master *master,
			       struct spi_device *spi, struct spi_transfer *t)
{
	struct spi_st *spi_st = spi_master_get_devdata(master);
	uint32_t ctl = 0;

	/* Setup transfer */
	spi_st->tx_ptr = t->tx_buf;
	spi_st->rx_ptr = t->rx_buf;

	if (spi->bits_per_word > 8) {
		/*
		 * Anything greater than 8 bits-per-word requires 2
		 * bytes-per-word in the RX/TX buffers
		 */
		spi_st->bytes_per_word = 2;
		spi_st->words_remaining = t->len / 2;

	} else if (spi->bits_per_word == 8 && !(t->len & 0x1)) {
		/*
		 * If transfer is even-length, and 8 bits-per-word, then
		 * implement as half-length 16 bits-per-word transfer
		 */
		spi_st->bytes_per_word = 2;
		spi_st->words_remaining = t->len / 2;

		/* Set SSC_CTL to 16 bits-per-word */
		ctl = readl_relaxed(spi_st->base + SSC_CTL);
		writel_relaxed((ctl | 0xf), spi_st->base + SSC_CTL);

		readl_relaxed(spi_st->base + SSC_RBUF);

	} else {
		spi_st->bytes_per_word = 1;
		spi_st->words_remaining = t->len;
	}

	reinit_completion(&spi_st->done);

	/* Start transfer by writing to the TX FIFO */
	ssc_write_tx_fifo(spi_st);
	writel_relaxed(SSC_IEN_TEEN, spi_st->base + SSC_IEN);

	/* Wait for transfer to complete */
	wait_for_completion(&spi_st->done);

	/* Restore SSC_CTL if necessary */
	if (ctl)
		writel_relaxed(ctl, spi_st->base + SSC_CTL);

	spi_finalize_current_transfer(spi->master);

	return t->len;
}