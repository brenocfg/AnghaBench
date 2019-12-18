#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_transfer {int bits_per_word; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  master; } ;
struct spi_imx_data {int bits_per_word; int dynamic_burst; int usedma; TYPE_2__* devtype_data; int /*<<< orphan*/  slave_burst; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; scalar_t__ slave_mode; TYPE_1__ bitbang; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* prepare_transfer ) (struct spi_imx_data*,struct spi_device*,struct spi_transfer*) ;scalar_t__ dynamic_burst; } ;

/* Variables and functions */
 scalar_t__ is_imx53_ecspi (struct spi_imx_data*) ; 
 int /*<<< orphan*/  mx53_ecspi_rx_slave ; 
 int /*<<< orphan*/  mx53_ecspi_tx_slave ; 
 int /*<<< orphan*/  spi_imx_buf_rx_swap ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u16 ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u32 ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u8 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_swap ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u16 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u32 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u8 ; 
 scalar_t__ spi_imx_can_dma (int /*<<< orphan*/ ,struct spi_device*,struct spi_transfer*) ; 
 struct spi_imx_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_imx_data*,struct spi_device*,struct spi_transfer*) ; 

__attribute__((used)) static int spi_imx_setupxfer(struct spi_device *spi,
				 struct spi_transfer *t)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);

	if (!t)
		return 0;

	spi_imx->bits_per_word = t->bits_per_word;

	/*
	 * Initialize the functions for transfer. To transfer non byte-aligned
	 * words, we have to use multiple word-size bursts, we can't use
	 * dynamic_burst in that case.
	 */
	if (spi_imx->devtype_data->dynamic_burst && !spi_imx->slave_mode &&
	    (spi_imx->bits_per_word == 8 ||
	    spi_imx->bits_per_word == 16 ||
	    spi_imx->bits_per_word == 32)) {

		spi_imx->rx = spi_imx_buf_rx_swap;
		spi_imx->tx = spi_imx_buf_tx_swap;
		spi_imx->dynamic_burst = 1;

	} else {
		if (spi_imx->bits_per_word <= 8) {
			spi_imx->rx = spi_imx_buf_rx_u8;
			spi_imx->tx = spi_imx_buf_tx_u8;
		} else if (spi_imx->bits_per_word <= 16) {
			spi_imx->rx = spi_imx_buf_rx_u16;
			spi_imx->tx = spi_imx_buf_tx_u16;
		} else {
			spi_imx->rx = spi_imx_buf_rx_u32;
			spi_imx->tx = spi_imx_buf_tx_u32;
		}
		spi_imx->dynamic_burst = 0;
	}

	if (spi_imx_can_dma(spi_imx->bitbang.master, spi, t))
		spi_imx->usedma = 1;
	else
		spi_imx->usedma = 0;

	if (is_imx53_ecspi(spi_imx) && spi_imx->slave_mode) {
		spi_imx->rx = mx53_ecspi_rx_slave;
		spi_imx->tx = mx53_ecspi_tx_slave;
		spi_imx->slave_burst = t->len;
	}

	spi_imx->devtype_data->prepare_transfer(spi_imx, spi, t);

	return 0;
}