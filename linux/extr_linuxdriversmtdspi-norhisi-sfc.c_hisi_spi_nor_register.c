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
struct spi_nor_hwcaps {int mask; } ;
struct mtd_info {int /*<<< orphan*/  name; } ;
struct spi_nor {struct mtd_info mtd; int /*<<< orphan*/ * erase; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  unprepare; int /*<<< orphan*/  prepare; struct hifmc_priv* priv; struct device* dev; } ;
struct hifmc_priv {struct hifmc_host* host; int /*<<< orphan*/  clkrate; int /*<<< orphan*/  chipselect; } ;
struct hifmc_host {size_t num_chip; struct spi_nor** nor; struct device* dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_spi_nor_prep ; 
 int /*<<< orphan*/  hisi_spi_nor_read ; 
 int /*<<< orphan*/  hisi_spi_nor_read_reg ; 
 int /*<<< orphan*/  hisi_spi_nor_unprep ; 
 int /*<<< orphan*/  hisi_spi_nor_write ; 
 int /*<<< orphan*/  hisi_spi_nor_write_reg ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int spi_nor_scan (struct spi_nor*,int /*<<< orphan*/ *,struct spi_nor_hwcaps const*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (struct spi_nor*,struct device_node*) ; 

__attribute__((used)) static int hisi_spi_nor_register(struct device_node *np,
				struct hifmc_host *host)
{
	const struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_READ_1_1_2 |
			SNOR_HWCAPS_READ_1_1_4 |
			SNOR_HWCAPS_PP,
	};
	struct device *dev = host->dev;
	struct spi_nor *nor;
	struct hifmc_priv *priv;
	struct mtd_info *mtd;
	int ret;

	nor = devm_kzalloc(dev, sizeof(*nor), GFP_KERNEL);
	if (!nor)
		return -ENOMEM;

	nor->dev = dev;
	spi_nor_set_flash_node(nor, np);

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = of_property_read_u32(np, "reg", &priv->chipselect);
	if (ret) {
		dev_err(dev, "There's no reg property for %pOF\n",
			np);
		return ret;
	}

	ret = of_property_read_u32(np, "spi-max-frequency",
			&priv->clkrate);
	if (ret) {
		dev_err(dev, "There's no spi-max-frequency property for %pOF\n",
			np);
		return ret;
	}
	priv->host = host;
	nor->priv = priv;

	nor->prepare = hisi_spi_nor_prep;
	nor->unprepare = hisi_spi_nor_unprep;
	nor->read_reg = hisi_spi_nor_read_reg;
	nor->write_reg = hisi_spi_nor_write_reg;
	nor->read = hisi_spi_nor_read;
	nor->write = hisi_spi_nor_write;
	nor->erase = NULL;
	ret = spi_nor_scan(nor, NULL, &hwcaps);
	if (ret)
		return ret;

	mtd = &nor->mtd;
	mtd->name = np->name;
	ret = mtd_device_register(mtd, NULL, 0);
	if (ret)
		return ret;

	host->nor[host->num_chip] = nor;
	host->num_chip++;
	return 0;
}