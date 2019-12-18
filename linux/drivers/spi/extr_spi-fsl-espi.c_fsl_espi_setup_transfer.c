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
typedef  int u32 ;
struct spi_transfer {int bits_per_word; int speed_hz; } ;
struct spi_device {int bits_per_word; int max_speed_hz; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;
struct fsl_espi_cs {int hw_mode; } ;
struct fsl_espi {int /*<<< orphan*/  spibrg; } ;

/* Variables and functions */
 int CSMODE_DIV16 ; 
 int CSMODE_LEN (int) ; 
 int CSMODE_PM (int) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESPI_SPMODEx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_espi_write_reg (struct fsl_espi*,int /*<<< orphan*/ ,int) ; 
 struct fsl_espi_cs* spi_get_ctldata (struct spi_device*) ; 
 struct fsl_espi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_espi_setup_transfer(struct spi_device *spi,
					struct spi_transfer *t)
{
	struct fsl_espi *espi = spi_master_get_devdata(spi->master);
	int bits_per_word = t ? t->bits_per_word : spi->bits_per_word;
	u32 pm, hz = t ? t->speed_hz : spi->max_speed_hz;
	struct fsl_espi_cs *cs = spi_get_ctldata(spi);
	u32 hw_mode_old = cs->hw_mode;

	/* mask out bits we are going to set */
	cs->hw_mode &= ~(CSMODE_LEN(0xF) | CSMODE_DIV16 | CSMODE_PM(0xF));

	cs->hw_mode |= CSMODE_LEN(bits_per_word - 1);

	pm = DIV_ROUND_UP(espi->spibrg, hz * 4) - 1;

	if (pm > 15) {
		cs->hw_mode |= CSMODE_DIV16;
		pm = DIV_ROUND_UP(espi->spibrg, hz * 16 * 4) - 1;
	}

	cs->hw_mode |= CSMODE_PM(pm);

	/* don't write the mode register if the mode doesn't change */
	if (cs->hw_mode != hw_mode_old)
		fsl_espi_write_reg(espi, ESPI_SPMODEx(spi->chip_select),
				   cs->hw_mode);
}