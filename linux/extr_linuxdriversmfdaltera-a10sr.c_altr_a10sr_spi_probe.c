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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct altr_a10sr {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  altr_a10sr_regmap_config ; 
 int /*<<< orphan*/  altr_a10sr_subdev_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct altr_a10sr* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct altr_a10sr*) ; 
 int /*<<< orphan*/  spi_setup (struct spi_device*) ; 

__attribute__((used)) static int altr_a10sr_spi_probe(struct spi_device *spi)
{
	int ret;
	struct altr_a10sr *a10sr;

	a10sr = devm_kzalloc(&spi->dev, sizeof(*a10sr),
			     GFP_KERNEL);
	if (!a10sr)
		return -ENOMEM;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	a10sr->dev = &spi->dev;

	spi_set_drvdata(spi, a10sr);

	a10sr->regmap = devm_regmap_init_spi(spi, &altr_a10sr_regmap_config);
	if (IS_ERR(a10sr->regmap)) {
		ret = PTR_ERR(a10sr->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = devm_mfd_add_devices(a10sr->dev, PLATFORM_DEVID_AUTO,
				   altr_a10sr_subdev_info,
				   ARRAY_SIZE(altr_a10sr_subdev_info),
				   NULL, 0, NULL);
	if (ret)
		dev_err(a10sr->dev, "Failed to register sub-devices: %d\n",
			ret);

	return ret;
}