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
struct spi_transfer {int bits_per_word; scalar_t__ len; scalar_t__ speed_hz; } ;
struct spi_device {int bits_per_word; scalar_t__ max_speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  mode; int /*<<< orphan*/  controller; } ;
struct spi_controller {int dummy; } ;
struct TYPE_2__ {int bpw; scalar_t__ speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  mode; } ;
struct fsl_lpspi_data {scalar_t__ txfifosize; scalar_t__ watermark; int usedma; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u16 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u32 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_rx_u8 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u16 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u32 ; 
 int /*<<< orphan*/  fsl_lpspi_buf_tx_u8 ; 
 scalar_t__ fsl_lpspi_can_dma (struct spi_controller*,struct spi_device*,struct spi_transfer*) ; 
 int fsl_lpspi_config (struct fsl_lpspi_data*) ; 
 struct fsl_lpspi_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_lpspi_setup_transfer(struct spi_controller *controller,
				     struct spi_device *spi,
				     struct spi_transfer *t)
{
	struct fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(spi->controller);

	if (t == NULL)
		return -EINVAL;

	fsl_lpspi->config.mode = spi->mode;
	fsl_lpspi->config.bpw = t->bits_per_word;
	fsl_lpspi->config.speed_hz = t->speed_hz;
	fsl_lpspi->config.chip_select = spi->chip_select;

	if (!fsl_lpspi->config.speed_hz)
		fsl_lpspi->config.speed_hz = spi->max_speed_hz;
	if (!fsl_lpspi->config.bpw)
		fsl_lpspi->config.bpw = spi->bits_per_word;

	/* Initialize the functions for transfer */
	if (fsl_lpspi->config.bpw <= 8) {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u8;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u8;
	} else if (fsl_lpspi->config.bpw <= 16) {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u16;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u16;
	} else {
		fsl_lpspi->rx = fsl_lpspi_buf_rx_u32;
		fsl_lpspi->tx = fsl_lpspi_buf_tx_u32;
	}

	if (t->len <= fsl_lpspi->txfifosize)
		fsl_lpspi->watermark = t->len;
	else
		fsl_lpspi->watermark = fsl_lpspi->txfifosize;

	if (fsl_lpspi_can_dma(controller, spi, t))
		fsl_lpspi->usedma = 1;
	else
		fsl_lpspi->usedma = 0;

	return fsl_lpspi_config(fsl_lpspi);
}