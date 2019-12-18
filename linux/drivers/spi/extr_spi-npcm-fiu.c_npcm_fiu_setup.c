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
struct spi_device {size_t chip_select; int /*<<< orphan*/  max_speed_hz; struct spi_controller* master; } ;
struct spi_controller {int dummy; } ;
struct npcm_fiu_spi {int /*<<< orphan*/  clk; int /*<<< orphan*/  clkrate; struct npcm_fiu_chip* chip; } ;
struct npcm_fiu_chip {size_t chipselect; int /*<<< orphan*/  clkrate; struct npcm_fiu_spi* fiu; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 struct npcm_fiu_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int npcm_fiu_setup(struct spi_device *spi)
{
	struct spi_controller *ctrl = spi->master;
	struct npcm_fiu_spi *fiu = spi_controller_get_devdata(ctrl);
	struct npcm_fiu_chip *chip;

	chip = &fiu->chip[spi->chip_select];
	chip->fiu = fiu;
	chip->chipselect = spi->chip_select;
	chip->clkrate = spi->max_speed_hz;

	fiu->clkrate = clk_get_rate(fiu->clk);

	return 0;
}