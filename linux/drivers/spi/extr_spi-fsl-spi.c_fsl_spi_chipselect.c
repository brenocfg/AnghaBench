#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_mpc8xxx_cs {int /*<<< orphan*/  get_tx; int /*<<< orphan*/  get_rx; int /*<<< orphan*/  tx_shift; int /*<<< orphan*/  rx_shift; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct spi_device {int mode; TYPE_3__ dev; struct spi_mpc8xxx_cs* controller_state; int /*<<< orphan*/  master; } ;
struct mpc8xxx_spi {int /*<<< orphan*/  get_tx; int /*<<< orphan*/  get_rx; int /*<<< orphan*/  tx_shift; int /*<<< orphan*/  rx_shift; } ;
struct fsl_spi_platform_data {int /*<<< orphan*/  (* cs_control ) (struct spi_device*,int) ;} ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {struct fsl_spi_platform_data* platform_data; } ;

/* Variables and functions */
 int BITBANG_CS_ACTIVE ; 
 int BITBANG_CS_INACTIVE ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  fsl_spi_change_mode (struct spi_device*) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct spi_device*,int) ; 

__attribute__((used)) static void fsl_spi_chipselect(struct spi_device *spi, int value)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct fsl_spi_platform_data *pdata;
	bool pol = spi->mode & SPI_CS_HIGH;
	struct spi_mpc8xxx_cs	*cs = spi->controller_state;

	pdata = spi->dev.parent->parent->platform_data;

	if (value == BITBANG_CS_INACTIVE) {
		if (pdata->cs_control)
			pdata->cs_control(spi, !pol);
	}

	if (value == BITBANG_CS_ACTIVE) {
		mpc8xxx_spi->rx_shift = cs->rx_shift;
		mpc8xxx_spi->tx_shift = cs->tx_shift;
		mpc8xxx_spi->get_rx = cs->get_rx;
		mpc8xxx_spi->get_tx = cs->get_tx;

		fsl_spi_change_mode(spi);

		if (pdata->cs_control)
			pdata->cs_control(spi, pol);
	}
}