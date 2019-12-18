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
struct spi_device {int mode; int /*<<< orphan*/  chip_select; struct s3c24xx_spi_devstate* controller_state; } ;
struct s3c24xx_spi_devstate {int spcon; } ;
struct s3c24xx_spi {int /*<<< orphan*/  pdata; int /*<<< orphan*/  (* set_cs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;scalar_t__ regs; } ;

/* Variables and functions */
#define  BITBANG_CS_ACTIVE 129 
#define  BITBANG_CS_INACTIVE 128 
 scalar_t__ S3C2410_SPCON ; 
 int S3C2410_SPCON_ENSCK ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct s3c24xx_spi* to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void s3c24xx_spi_chipsel(struct spi_device *spi, int value)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	unsigned int cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;

	/* change the chipselect state and the state of the spi engine clock */

	switch (value) {
	case BITBANG_CS_INACTIVE:
		hw->set_cs(hw->pdata, spi->chip_select, cspol^1);
		writeb(cs->spcon, hw->regs + S3C2410_SPCON);
		break;

	case BITBANG_CS_ACTIVE:
		writeb(cs->spcon | S3C2410_SPCON_ENSCK,
		       hw->regs + S3C2410_SPCON);
		hw->set_cs(hw->pdata, spi->chip_select, cspol);
		break;
	}
}