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
struct spi_device {unsigned int chip_select; int mode; int /*<<< orphan*/  master; } ;
struct ppc4xx_spi {int /*<<< orphan*/ * gpios; TYPE_1__* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_chipselect; } ;

/* Variables and functions */
 int BITBANG_CS_INACTIVE ; 
 int /*<<< orphan*/  EEXIST ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,unsigned int) ; 
 struct ppc4xx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_ppc4xx_chipsel(struct spi_device *spi, int value)
{
	struct ppc4xx_spi *hw = spi_master_get_devdata(spi->master);
	unsigned int cs = spi->chip_select;
	unsigned int cspol;

	/*
	 * If there are no chip selects at all, or if this is the special
	 * case of a non-existent (dummy) chip select, do nothing.
	 */

	if (!hw->master->num_chipselect || hw->gpios[cs] == -EEXIST)
		return;

	cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;
	if (value == BITBANG_CS_INACTIVE)
		cspol = !cspol;

	gpio_set_value(hw->gpios[cs], cspol);
}