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
struct spi_imx_data {unsigned int remainder; unsigned int count; scalar_t__ txfifo; TYPE_1__* devtype_data; int /*<<< orphan*/  slave_mode; int /*<<< orphan*/  (* tx ) (struct spi_imx_data*) ;scalar_t__ dynamic_burst; int /*<<< orphan*/  bits_per_word; } ;
struct TYPE_2__ {scalar_t__ fifo_size; int /*<<< orphan*/  (* trigger ) (struct spi_imx_data*) ;} ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int MX51_ECSPI_CTRL_MAX_BURST ; 
 unsigned int spi_imx_bytes_per_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_imx_set_burst_len (struct spi_imx_data*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct spi_imx_data*) ; 
 int /*<<< orphan*/  stub2 (struct spi_imx_data*) ; 

__attribute__((used)) static void spi_imx_push(struct spi_imx_data *spi_imx)
{
	unsigned int burst_len, fifo_words;

	if (spi_imx->dynamic_burst)
		fifo_words = 4;
	else
		fifo_words = spi_imx_bytes_per_word(spi_imx->bits_per_word);
	/*
	 * Reload the FIFO when the remaining bytes to be transferred in the
	 * current burst is 0. This only applies when bits_per_word is a
	 * multiple of 8.
	 */
	if (!spi_imx->remainder) {
		if (spi_imx->dynamic_burst) {

			/* We need to deal unaligned data first */
			burst_len = spi_imx->count % MX51_ECSPI_CTRL_MAX_BURST;

			if (!burst_len)
				burst_len = MX51_ECSPI_CTRL_MAX_BURST;

			spi_imx_set_burst_len(spi_imx, burst_len * 8);

			spi_imx->remainder = burst_len;
		} else {
			spi_imx->remainder = fifo_words;
		}
	}

	while (spi_imx->txfifo < spi_imx->devtype_data->fifo_size) {
		if (!spi_imx->count)
			break;
		if (spi_imx->dynamic_burst &&
		    spi_imx->txfifo >= DIV_ROUND_UP(spi_imx->remainder,
						     fifo_words))
			break;
		spi_imx->tx(spi_imx);
		spi_imx->txfifo++;
	}

	if (!spi_imx->slave_mode)
		spi_imx->devtype_data->trigger(spi_imx);
}