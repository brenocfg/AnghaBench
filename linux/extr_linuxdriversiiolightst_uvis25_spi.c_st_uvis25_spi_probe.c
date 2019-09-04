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
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int st_uvis25_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regmap*) ; 
 int /*<<< orphan*/  st_uvis25_spi_regmap_config ; 

__attribute__((used)) static int st_uvis25_spi_probe(struct spi_device *spi)
{
	struct regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &st_uvis25_spi_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&spi->dev, "Failed to register spi regmap %d\n",
			(int)PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return st_uvis25_probe(&spi->dev, spi->irq, regmap);
}