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
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ad714x_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPI ; 
 scalar_t__ IS_ERR (struct ad714x_chip*) ; 
 int PTR_ERR (struct ad714x_chip*) ; 
 struct ad714x_chip* ad714x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad714x_spi_read ; 
 int /*<<< orphan*/  ad714x_spi_write ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ad714x_chip*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ad714x_spi_probe(struct spi_device *spi)
{
	struct ad714x_chip *chip;
	int err;

	spi->bits_per_word = 8;
	err = spi_setup(spi);
	if (err < 0)
		return err;

	chip = ad714x_probe(&spi->dev, BUS_SPI, spi->irq,
			    ad714x_spi_read, ad714x_spi_write);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	spi_set_drvdata(spi, chip);

	return 0;
}