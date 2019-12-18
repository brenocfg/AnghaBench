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
typedef  int u32 ;
struct spi_device {int chip_select; int mode; int /*<<< orphan*/  dev; TYPE_2__* master; struct atmel_spi_device* controller_state; } ;
struct atmel_spi_device {int csr; int /*<<< orphan*/  npcs_pin; } ;
struct TYPE_3__ {scalar_t__ has_wdrbt; } ;
struct atmel_spi {scalar_t__ use_cs_gpios; TYPE_1__ caps; } ;
struct TYPE_4__ {int num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPOL ; 
 scalar_t__ CSR0 ; 
 int /*<<< orphan*/  MODFDIS ; 
 scalar_t__ MR ; 
 int /*<<< orphan*/  MSTR ; 
 int /*<<< orphan*/  PCS ; 
 int SPI_BF (int /*<<< orphan*/ ,int) ; 
 int SPI_BFINS (int /*<<< orphan*/ ,int,int) ; 
 int SPI_BIT (int /*<<< orphan*/ ) ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  WDRBT ; 
 scalar_t__ atmel_spi_is_v2 (struct atmel_spi*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int spi_readl (struct atmel_spi*,scalar_t__) ; 
 int /*<<< orphan*/  spi_writel (struct atmel_spi*,scalar_t__,int) ; 

__attribute__((used)) static void cs_activate(struct atmel_spi *as, struct spi_device *spi)
{
	struct atmel_spi_device *asd = spi->controller_state;
	u32 mr;

	if (atmel_spi_is_v2(as)) {
		spi_writel(as, CSR0 + 4 * spi->chip_select, asd->csr);
		/* For the low SPI version, there is a issue that PDC transfer
		 * on CS1,2,3 needs SPI_CSR0.BITS config as SPI_CSR1,2,3.BITS
		 */
		spi_writel(as, CSR0, asd->csr);
		if (as->caps.has_wdrbt) {
			spi_writel(as, MR,
					SPI_BF(PCS, ~(0x01 << spi->chip_select))
					| SPI_BIT(WDRBT)
					| SPI_BIT(MODFDIS)
					| SPI_BIT(MSTR));
		} else {
			spi_writel(as, MR,
					SPI_BF(PCS, ~(0x01 << spi->chip_select))
					| SPI_BIT(MODFDIS)
					| SPI_BIT(MSTR));
		}

		mr = spi_readl(as, MR);
		if (as->use_cs_gpios)
			gpiod_set_value(asd->npcs_pin, 1);
	} else {
		u32 cpol = (spi->mode & SPI_CPOL) ? SPI_BIT(CPOL) : 0;
		int i;
		u32 csr;

		/* Make sure clock polarity is correct */
		for (i = 0; i < spi->master->num_chipselect; i++) {
			csr = spi_readl(as, CSR0 + 4 * i);
			if ((csr ^ cpol) & SPI_BIT(CPOL))
				spi_writel(as, CSR0 + 4 * i,
						csr ^ SPI_BIT(CPOL));
		}

		mr = spi_readl(as, MR);
		mr = SPI_BFINS(PCS, ~(1 << spi->chip_select), mr);
		if (as->use_cs_gpios && spi->chip_select != 0)
			gpiod_set_value(asd->npcs_pin, 1);
		spi_writel(as, MR, mr);
	}

	dev_dbg(&spi->dev, "activate NPCS, mr %08x\n", mr);
}