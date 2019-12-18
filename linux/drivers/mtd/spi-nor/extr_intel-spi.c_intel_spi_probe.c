#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int mask; } ;
struct resource {int dummy; } ;
struct mtd_partition {int dummy; } ;
struct intel_spi_boardinfo {int /*<<< orphan*/  writeable; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__ mtd; int /*<<< orphan*/  erase; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; struct intel_spi* priv; struct device* dev; } ;
struct intel_spi {TYPE_1__ nor; int /*<<< orphan*/  writeable; struct device* dev; struct intel_spi_boardinfo const* info; int /*<<< orphan*/  base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct intel_spi* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct intel_spi* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_WRITEABLE ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct intel_spi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_spi_erase ; 
 int /*<<< orphan*/  intel_spi_fill_partition (struct intel_spi*,struct mtd_partition*) ; 
 int intel_spi_init (struct intel_spi*) ; 
 int /*<<< orphan*/  intel_spi_read ; 
 int /*<<< orphan*/  intel_spi_read_reg ; 
 int /*<<< orphan*/  intel_spi_write ; 
 int /*<<< orphan*/  intel_spi_write_reg ; 
 int mtd_device_register (TYPE_2__*,struct mtd_partition*,int) ; 
 int spi_nor_scan (TYPE_1__*,int /*<<< orphan*/ *,struct spi_nor_hwcaps const*) ; 
 int /*<<< orphan*/  writeable ; 

struct intel_spi *intel_spi_probe(struct device *dev,
	struct resource *mem, const struct intel_spi_boardinfo *info)
{
	const struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	};
	struct mtd_partition part;
	struct intel_spi *ispi;
	int ret;

	if (!info || !mem)
		return ERR_PTR(-EINVAL);

	ispi = devm_kzalloc(dev, sizeof(*ispi), GFP_KERNEL);
	if (!ispi)
		return ERR_PTR(-ENOMEM);

	ispi->base = devm_ioremap_resource(dev, mem);
	if (IS_ERR(ispi->base))
		return ERR_CAST(ispi->base);

	ispi->dev = dev;
	ispi->info = info;
	ispi->writeable = info->writeable;

	ret = intel_spi_init(ispi);
	if (ret)
		return ERR_PTR(ret);

	ispi->nor.dev = ispi->dev;
	ispi->nor.priv = ispi;
	ispi->nor.read_reg = intel_spi_read_reg;
	ispi->nor.write_reg = intel_spi_write_reg;
	ispi->nor.read = intel_spi_read;
	ispi->nor.write = intel_spi_write;
	ispi->nor.erase = intel_spi_erase;

	ret = spi_nor_scan(&ispi->nor, NULL, &hwcaps);
	if (ret) {
		dev_info(dev, "failed to locate the chip\n");
		return ERR_PTR(ret);
	}

	intel_spi_fill_partition(ispi, &part);

	/* Prevent writes if not explicitly enabled */
	if (!ispi->writeable || !writeable)
		ispi->nor.mtd.flags &= ~MTD_WRITEABLE;

	ret = mtd_device_register(&ispi->nor.mtd, &part, 1);
	if (ret)
		return ERR_PTR(ret);

	return ispi;
}