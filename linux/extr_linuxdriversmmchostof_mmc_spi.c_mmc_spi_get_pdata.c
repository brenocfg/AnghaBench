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
typedef  int /*<<< orphan*/  u32 ;
struct device {struct mmc_spi_platform_data* platform_data; struct device_node* of_node; } ;
struct spi_device {struct device dev; } ;
struct mmc_spi_platform_data {int /*<<< orphan*/  caps; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  caps2; int /*<<< orphan*/  flags; int /*<<< orphan*/  ro_gpio; int /*<<< orphan*/  cd_gpio; int /*<<< orphan*/  ocr_mask; } ;
struct of_mmc_spi {int* alow_gpios; scalar_t__ detect_irq; struct mmc_spi_platform_data pdata; int /*<<< orphan*/ * gpios; } ;
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t CD_GPIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_CAP2_CD_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MMC_CAP2_RO_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MMC_CAP_NEEDS_POLL ; 
 int /*<<< orphan*/  MMC_SPI_USE_CD_GPIO ; 
 int /*<<< orphan*/  MMC_SPI_USE_RO_GPIO ; 
 int OF_GPIO_ACTIVE_LOW ; 
 size_t WP_GPIO ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct of_mmc_spi*) ; 
 struct of_mmc_spi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_vddrange_to_ocrmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_gpio_flags (struct device_node*,int,int*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_mmc_spi_exit ; 
 int /*<<< orphan*/  of_mmc_spi_init ; 

struct mmc_spi_platform_data *mmc_spi_get_pdata(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct device_node *np = dev->of_node;
	struct of_mmc_spi *oms;
	const __be32 *voltage_ranges;
	int num_ranges;
	int i;

	if (dev->platform_data || !np)
		return dev->platform_data;

	oms = kzalloc(sizeof(*oms), GFP_KERNEL);
	if (!oms)
		return NULL;

	voltage_ranges = of_get_property(np, "voltage-ranges", &num_ranges);
	num_ranges = num_ranges / sizeof(*voltage_ranges) / 2;
	if (!voltage_ranges || !num_ranges) {
		dev_err(dev, "OF: voltage-ranges unspecified\n");
		goto err_ocr;
	}

	for (i = 0; i < num_ranges; i++) {
		const int j = i * 2;
		u32 mask;

		mask = mmc_vddrange_to_ocrmask(be32_to_cpu(voltage_ranges[j]),
					       be32_to_cpu(voltage_ranges[j + 1]));
		if (!mask) {
			dev_err(dev, "OF: voltage-range #%d is invalid\n", i);
			goto err_ocr;
		}
		oms->pdata.ocr_mask |= mask;
	}

	for (i = 0; i < ARRAY_SIZE(oms->gpios); i++) {
		enum of_gpio_flags gpio_flags;

		oms->gpios[i] = of_get_gpio_flags(np, i, &gpio_flags);
		if (!gpio_is_valid(oms->gpios[i]))
			continue;

		if (gpio_flags & OF_GPIO_ACTIVE_LOW)
			oms->alow_gpios[i] = true;
	}

	if (gpio_is_valid(oms->gpios[CD_GPIO])) {
		oms->pdata.cd_gpio = oms->gpios[CD_GPIO];
		oms->pdata.flags |= MMC_SPI_USE_CD_GPIO;
		if (!oms->alow_gpios[CD_GPIO])
			oms->pdata.caps2 |= MMC_CAP2_CD_ACTIVE_HIGH;
	}
	if (gpio_is_valid(oms->gpios[WP_GPIO])) {
		oms->pdata.ro_gpio = oms->gpios[WP_GPIO];
		oms->pdata.flags |= MMC_SPI_USE_RO_GPIO;
		if (!oms->alow_gpios[WP_GPIO])
			oms->pdata.caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;
	}

	oms->detect_irq = irq_of_parse_and_map(np, 0);
	if (oms->detect_irq != 0) {
		oms->pdata.init = of_mmc_spi_init;
		oms->pdata.exit = of_mmc_spi_exit;
	} else {
		oms->pdata.caps |= MMC_CAP_NEEDS_POLL;
	}

	dev->platform_data = &oms->pdata;
	return dev->platform_data;
err_ocr:
	kfree(oms);
	return NULL;
}