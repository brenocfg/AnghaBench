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
struct spi_device_id {int /*<<< orphan*/  driver_data; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; } ;
struct regmap_config {int read_flag_mask; int reg_bits; int pad_bits; int val_bits; int use_single_read; int use_single_write; } ;
struct da9052 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  chip_irq; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int da9052_device_init (struct da9052*,int /*<<< orphan*/ ) ; 
 struct regmap_config da9052_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct da9052* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,struct regmap_config*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct da9052*) ; 
 int /*<<< orphan*/  spi_setup (struct spi_device*) ; 

__attribute__((used)) static int da9052_spi_probe(struct spi_device *spi)
{
	struct regmap_config config;
	int ret;
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct da9052 *da9052;

	da9052 = devm_kzalloc(&spi->dev, sizeof(struct da9052), GFP_KERNEL);
	if (!da9052)
		return -ENOMEM;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	spi_setup(spi);

	da9052->dev = &spi->dev;
	da9052->chip_irq = spi->irq;

	spi_set_drvdata(spi, da9052);

	config = da9052_regmap_config;
	config.read_flag_mask = 1;
	config.reg_bits = 7;
	config.pad_bits = 1;
	config.val_bits = 8;
	config.use_single_read = true;
	config.use_single_write = true;

	da9052->regmap = devm_regmap_init_spi(spi, &config);
	if (IS_ERR(da9052->regmap)) {
		ret = PTR_ERR(da9052->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	return da9052_device_init(da9052, id->driver_data);
}