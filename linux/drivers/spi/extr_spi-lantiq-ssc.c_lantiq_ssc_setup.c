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
struct spi_master {int dummy; } ;
struct spi_device {unsigned int chip_select; int mode; int /*<<< orphan*/  cs_gpio; struct spi_master* master; } ;
struct lantiq_ssc_spi {unsigned int base_cs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LTQ_SPI_GPOCON ; 
 unsigned int LTQ_SPI_GPOCON_ISCSBN_S ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct lantiq_ssc_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int lantiq_ssc_setup(struct spi_device *spidev)
{
	struct spi_master *master = spidev->master;
	struct lantiq_ssc_spi *spi = spi_master_get_devdata(master);
	unsigned int cs = spidev->chip_select;
	u32 gpocon;

	/* GPIOs are used for CS */
	if (gpio_is_valid(spidev->cs_gpio))
		return 0;

	dev_dbg(spi->dev, "using internal chipselect %u\n", cs);

	if (cs < spi->base_cs) {
		dev_err(spi->dev,
			"chipselect %i too small (min %i)\n", cs, spi->base_cs);
		return -EINVAL;
	}

	/* set GPO pin to CS mode */
	gpocon = 1 << ((cs - spi->base_cs) + LTQ_SPI_GPOCON_ISCSBN_S);

	/* invert GPO pin */
	if (spidev->mode & SPI_CS_HIGH)
		gpocon |= 1 << (cs - spi->base_cs);

	lantiq_ssc_maskl(spi, 0, gpocon, LTQ_SPI_GPOCON);

	return 0;
}