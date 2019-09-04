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
struct tps65912 {int /*<<< orphan*/  regmap; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq; } ;
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tps65912* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tps65912*) ; 
 int tps65912_device_init (struct tps65912*) ; 
 int /*<<< orphan*/  tps65912_regmap_config ; 

__attribute__((used)) static int tps65912_spi_probe(struct spi_device *spi)
{
	struct tps65912 *tps;

	tps = devm_kzalloc(&spi->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	spi_set_drvdata(spi, tps);
	tps->dev = &spi->dev;
	tps->irq = spi->irq;

	tps->regmap = devm_regmap_init_spi(spi, &tps65912_regmap_config);
	if (IS_ERR(tps->regmap)) {
		dev_err(tps->dev, "Failed to initialize register map\n");
		return PTR_ERR(tps->regmap);
	}

	return tps65912_device_init(tps);
}