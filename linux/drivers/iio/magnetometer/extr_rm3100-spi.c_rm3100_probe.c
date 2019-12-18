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
struct spi_device {int max_speed_hz; int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int rm3100_common_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm3100_regmap_config ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int rm3100_probe(struct spi_device *spi)
{
	struct regmap *regmap;
	int ret;

	/* Actually this device supports both mode 0 and mode 3. */
	spi->mode = SPI_MODE_0;
	/* Data rates cannot exceed 1Mbits. */
	spi->max_speed_hz = 1000000;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret)
		return ret;

	regmap = devm_regmap_init_spi(spi, &rm3100_regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return rm3100_common_probe(&spi->dev, regmap, spi->irq);
}