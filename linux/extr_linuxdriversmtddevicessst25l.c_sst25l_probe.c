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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int erasesize; int writesize; int writebufsize; int size; int /*<<< orphan*/  numeraseregions; scalar_t__ name; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_1__ dev; } ;
struct sst25l_flash {TYPE_2__ mtd; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct flash_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; scalar_t__ name; } ;
struct flash_info {int erase_size; int page_size; int nr_pages; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_NORFLASH ; 
 int /*<<< orphan*/  MTD_NORFLASH ; 
 struct flash_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,long long) ; 
 struct sst25l_flash* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,long long,long long,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct sst25l_flash*) ; 
 int /*<<< orphan*/  sst25l_erase ; 
 struct flash_info* sst25l_match_device (struct spi_device*) ; 
 int /*<<< orphan*/  sst25l_read ; 
 int /*<<< orphan*/  sst25l_write ; 

__attribute__((used)) static int sst25l_probe(struct spi_device *spi)
{
	struct flash_info *flash_info;
	struct sst25l_flash *flash;
	struct flash_platform_data *data;
	int ret;

	flash_info = sst25l_match_device(spi);
	if (!flash_info)
		return -ENODEV;

	flash = devm_kzalloc(&spi->dev, sizeof(*flash), GFP_KERNEL);
	if (!flash)
		return -ENOMEM;

	flash->spi = spi;
	mutex_init(&flash->lock);
	spi_set_drvdata(spi, flash);

	data = dev_get_platdata(&spi->dev);
	if (data && data->name)
		flash->mtd.name = data->name;

	flash->mtd.dev.parent   = &spi->dev;
	flash->mtd.type		= MTD_NORFLASH;
	flash->mtd.flags	= MTD_CAP_NORFLASH;
	flash->mtd.erasesize	= flash_info->erase_size;
	flash->mtd.writesize	= flash_info->page_size;
	flash->mtd.writebufsize	= flash_info->page_size;
	flash->mtd.size		= flash_info->page_size * flash_info->nr_pages;
	flash->mtd._erase	= sst25l_erase;
	flash->mtd._read		= sst25l_read;
	flash->mtd._write 	= sst25l_write;

	dev_info(&spi->dev, "%s (%lld KiB)\n", flash_info->name,
		 (long long)flash->mtd.size >> 10);

	pr_debug("mtd .name = %s, .size = 0x%llx (%lldMiB) "
	      ".erasesize = 0x%.8x (%uKiB) .numeraseregions = %d\n",
	      flash->mtd.name,
	      (long long)flash->mtd.size, (long long)(flash->mtd.size >> 20),
	      flash->mtd.erasesize, flash->mtd.erasesize / 1024,
	      flash->mtd.numeraseregions);


	ret = mtd_device_register(&flash->mtd, data ? data->parts : NULL,
				  data ? data->nr_parts : 0);
	if (ret)
		return -ENODEV;

	return 0;
}