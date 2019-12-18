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
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; scalar_t__ max_speed_hz; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MODE_0 ; 
 scalar_t__ TSC2005_SPI_MAX_SPEED_HZ ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  tsc2005_cmd ; 
 int /*<<< orphan*/  tsc2005_input_id ; 
 int tsc200x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc200x_regmap_config ; 

__attribute__((used)) static int tsc2005_probe(struct spi_device *spi)
{
	int error;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	if (!spi->max_speed_hz)
		spi->max_speed_hz = TSC2005_SPI_MAX_SPEED_HZ;

	error = spi_setup(spi);
	if (error)
		return error;

	return tsc200x_probe(&spi->dev, spi->irq, &tsc2005_input_id,
			     devm_regmap_init_spi(spi, &tsc200x_regmap_config),
			     tsc2005_cmd);
}