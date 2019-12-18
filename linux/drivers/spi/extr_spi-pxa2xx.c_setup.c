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
typedef  int uint ;
struct spi_device {int chip_select; int bits_per_word; int mode; int /*<<< orphan*/  dev; struct pxa2xx_spi_chip* controller_data; int /*<<< orphan*/  controller; } ;
struct pxa2xx_spi_chip {int tx_threshold; int tx_hi_threshold; int rx_threshold; scalar_t__ enable_loopback; scalar_t__ timeout; } ;
struct lpss_config {int tx_threshold_lo; int tx_threshold_hi; int rx_threshold; } ;
struct driver_data {int ssp_type; int /*<<< orphan*/  controller; TYPE_1__* controller_info; } ;
struct chip_data {int frm; int cr1; int lpss_tx_threshold; int threshold; int n_bytes; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  dma_burst_size; scalar_t__ dma_threshold; scalar_t__ enable_dma; int /*<<< orphan*/  lpss_rx_threshold; scalar_t__ timeout; } ;
struct TYPE_2__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 int CE4100_SSCR1_RFT ; 
 int CE4100_SSCR1_RxTresh (int) ; 
 int CE4100_SSCR1_TFT ; 
 int CE4100_SSCR1_TxTresh (int) ; 
#define  CE4100_SSP 135 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  LPSS_BSW_SSP 134 
#define  LPSS_BXT_SSP 133 
#define  LPSS_BYT_SSP 132 
#define  LPSS_CNL_SSP 131 
#define  LPSS_LPT_SSP 130 
#define  LPSS_SPT_SSP 129 
 int QUARK_X1000_SSCR1_RFT ; 
 int QUARK_X1000_SSCR1_RxTresh (int) ; 
 int QUARK_X1000_SSCR1_TFT ; 
 int QUARK_X1000_SSCR1_TxTresh (int) ; 
#define  QUARK_X1000_SSP 128 
 int RX_THRESH_CE4100_DFLT ; 
 int RX_THRESH_DFLT ; 
 int RX_THRESH_QUARK_X1000_DFLT ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int SSCR1_LBM ; 
 int SSCR1_RFT ; 
 int SSCR1_RxTresh (int) ; 
 int SSCR1_SCFR ; 
 int SSCR1_SCLKDIR ; 
 int SSCR1_SFRMDIR ; 
 int SSCR1_SPH ; 
 int SSCR1_SPO ; 
 int SSCR1_TFT ; 
 int SSCR1_TxTresh (int) ; 
 int /*<<< orphan*/  SSIRF_RxThresh (int) ; 
 int SSITF_TxHiThresh (int) ; 
 int SSITF_TxLoThresh (int) ; 
 scalar_t__ TIMOUT_DFLT ; 
 int TX_THRESH_CE4100_DFLT ; 
 int TX_THRESH_DFLT ; 
 int TX_THRESH_QUARK_X1000_DFLT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct lpss_config* lpss_get_config (struct driver_data*) ; 
 scalar_t__ pxa2xx_spi_set_dma_burst_and_threshold (struct chip_data*,struct spi_device*,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int setup_cs (struct spi_device*,struct chip_data*,struct pxa2xx_spi_chip*) ; 
 struct driver_data* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct chip_data*) ; 
 int /*<<< orphan*/  u16_reader ; 
 int /*<<< orphan*/  u16_writer ; 
 int /*<<< orphan*/  u32_reader ; 
 int /*<<< orphan*/  u32_writer ; 
 int /*<<< orphan*/  u8_reader ; 
 int /*<<< orphan*/  u8_writer ; 

__attribute__((used)) static int setup(struct spi_device *spi)
{
	struct pxa2xx_spi_chip *chip_info;
	struct chip_data *chip;
	const struct lpss_config *config;
	struct driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	uint tx_thres, tx_hi_thres, rx_thres;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		tx_thres = TX_THRESH_QUARK_X1000_DFLT;
		tx_hi_thres = 0;
		rx_thres = RX_THRESH_QUARK_X1000_DFLT;
		break;
	case CE4100_SSP:
		tx_thres = TX_THRESH_CE4100_DFLT;
		tx_hi_thres = 0;
		rx_thres = RX_THRESH_CE4100_DFLT;
		break;
	case LPSS_LPT_SSP:
	case LPSS_BYT_SSP:
	case LPSS_BSW_SSP:
	case LPSS_SPT_SSP:
	case LPSS_BXT_SSP:
	case LPSS_CNL_SSP:
		config = lpss_get_config(drv_data);
		tx_thres = config->tx_threshold_lo;
		tx_hi_thres = config->tx_threshold_hi;
		rx_thres = config->rx_threshold;
		break;
	default:
		tx_hi_thres = 0;
		if (spi_controller_is_slave(drv_data->controller)) {
			tx_thres = 1;
			rx_thres = 2;
		} else {
			tx_thres = TX_THRESH_DFLT;
			rx_thres = RX_THRESH_DFLT;
		}
		break;
	}

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	if (!chip) {
		chip = kzalloc(sizeof(struct chip_data), GFP_KERNEL);
		if (!chip)
			return -ENOMEM;

		if (drv_data->ssp_type == CE4100_SSP) {
			if (spi->chip_select > 4) {
				dev_err(&spi->dev,
					"failed setup: cs number must not be > 4.\n");
				kfree(chip);
				return -EINVAL;
			}

			chip->frm = spi->chip_select;
		}
		chip->enable_dma = drv_data->controller_info->enable_dma;
		chip->timeout = TIMOUT_DFLT;
	}

	/* protocol drivers may change the chip settings, so...
	 * if chip_info exists, use it */
	chip_info = spi->controller_data;

	/* chip_info isn't always needed */
	chip->cr1 = 0;
	if (chip_info) {
		if (chip_info->timeout)
			chip->timeout = chip_info->timeout;
		if (chip_info->tx_threshold)
			tx_thres = chip_info->tx_threshold;
		if (chip_info->tx_hi_threshold)
			tx_hi_thres = chip_info->tx_hi_threshold;
		if (chip_info->rx_threshold)
			rx_thres = chip_info->rx_threshold;
		chip->dma_threshold = 0;
		if (chip_info->enable_loopback)
			chip->cr1 = SSCR1_LBM;
	}
	if (spi_controller_is_slave(drv_data->controller)) {
		chip->cr1 |= SSCR1_SCFR;
		chip->cr1 |= SSCR1_SCLKDIR;
		chip->cr1 |= SSCR1_SFRMDIR;
		chip->cr1 |= SSCR1_SPH;
	}

	chip->lpss_rx_threshold = SSIRF_RxThresh(rx_thres);
	chip->lpss_tx_threshold = SSITF_TxLoThresh(tx_thres)
				| SSITF_TxHiThresh(tx_hi_thres);

	/* set dma burst and threshold outside of chip_info path so that if
	 * chip_info goes away after setting chip->enable_dma, the
	 * burst and threshold can still respond to changes in bits_per_word */
	if (chip->enable_dma) {
		/* set up legal burst and threshold for dma */
		if (pxa2xx_spi_set_dma_burst_and_threshold(chip, spi,
						spi->bits_per_word,
						&chip->dma_burst_size,
						&chip->dma_threshold)) {
			dev_warn(&spi->dev,
				 "in setup: DMA burst size reduced to match bits_per_word\n");
		}
		dev_dbg(&spi->dev,
			"in setup: DMA burst size set to %u\n",
			chip->dma_burst_size);
	}

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		chip->threshold = (QUARK_X1000_SSCR1_RxTresh(rx_thres)
				   & QUARK_X1000_SSCR1_RFT)
				   | (QUARK_X1000_SSCR1_TxTresh(tx_thres)
				   & QUARK_X1000_SSCR1_TFT);
		break;
	case CE4100_SSP:
		chip->threshold = (CE4100_SSCR1_RxTresh(rx_thres) & CE4100_SSCR1_RFT) |
			(CE4100_SSCR1_TxTresh(tx_thres) & CE4100_SSCR1_TFT);
		break;
	default:
		chip->threshold = (SSCR1_RxTresh(rx_thres) & SSCR1_RFT) |
			(SSCR1_TxTresh(tx_thres) & SSCR1_TFT);
		break;
	}

	chip->cr1 &= ~(SSCR1_SPO | SSCR1_SPH);
	chip->cr1 |= (((spi->mode & SPI_CPHA) != 0) ? SSCR1_SPH : 0)
			| (((spi->mode & SPI_CPOL) != 0) ? SSCR1_SPO : 0);

	if (spi->mode & SPI_LOOP)
		chip->cr1 |= SSCR1_LBM;

	if (spi->bits_per_word <= 8) {
		chip->n_bytes = 1;
		chip->read = u8_reader;
		chip->write = u8_writer;
	} else if (spi->bits_per_word <= 16) {
		chip->n_bytes = 2;
		chip->read = u16_reader;
		chip->write = u16_writer;
	} else if (spi->bits_per_word <= 32) {
		chip->n_bytes = 4;
		chip->read = u32_reader;
		chip->write = u32_writer;
	}

	spi_set_ctldata(spi, chip);

	if (drv_data->ssp_type == CE4100_SSP)
		return 0;

	return setup_cs(spi, chip, chip_info);
}