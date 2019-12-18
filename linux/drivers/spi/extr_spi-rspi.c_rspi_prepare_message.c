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
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int mode; int /*<<< orphan*/  max_speed_hz; } ;
struct spi_controller {int dummy; } ;
struct rspi_data {int /*<<< orphan*/  sppcr; int /*<<< orphan*/  spcmd; int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSPI_SPCR ; 
 int /*<<< orphan*/  SPCMD_CPHA ; 
 int /*<<< orphan*/  SPCMD_CPOL ; 
 int /*<<< orphan*/  SPCMD_SSLKP ; 
 int SPCR_SPE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  SPPCR_SPLP ; 
 int qspi_setup_sequencer (struct rspi_data*,struct spi_message*) ; 
 int rspi_read8 (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_config_register (struct rspi_data*,int) ; 
 struct rspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int rspi_prepare_message(struct spi_controller *ctlr,
				struct spi_message *msg)
{
	struct rspi_data *rspi = spi_controller_get_devdata(ctlr);
	struct spi_device *spi = msg->spi;
	int ret;

	rspi->max_speed_hz = spi->max_speed_hz;

	rspi->spcmd = SPCMD_SSLKP;
	if (spi->mode & SPI_CPOL)
		rspi->spcmd |= SPCMD_CPOL;
	if (spi->mode & SPI_CPHA)
		rspi->spcmd |= SPCMD_CPHA;

	/* CMOS output mode and MOSI signal from previous transfer */
	rspi->sppcr = 0;
	if (spi->mode & SPI_LOOP)
		rspi->sppcr |= SPPCR_SPLP;

	set_config_register(rspi, 8);

	if (msg->spi->mode &
	    (SPI_TX_DUAL | SPI_TX_QUAD | SPI_RX_DUAL | SPI_RX_QUAD)) {
		/* Setup sequencer for messages with multiple transfer modes */
		ret = qspi_setup_sequencer(rspi, msg);
		if (ret < 0)
			return ret;
	}

	/* Enable SPI function in master mode */
	rspi_write8(rspi, rspi_read8(rspi, RSPI_SPCR) | SPCR_SPE, RSPI_SPCR);
	return 0;
}