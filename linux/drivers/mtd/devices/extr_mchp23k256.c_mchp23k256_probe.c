#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_9__ {TYPE_3__* parent; } ;
struct TYPE_12__ {int writesize; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_1__ dev; } ;
struct mchp23k256_flash {TYPE_4__ mtd; TYPE_2__* caps; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct flash_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_RAM ; 
 int /*<<< orphan*/  MTD_RAM ; 
 struct flash_platform_data* dev_get_platdata (TYPE_3__*) ; 
 struct mchp23k256_flash* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ mchp23k256_caps ; 
 int /*<<< orphan*/  mchp23k256_read ; 
 int mchp23k256_set_mode (struct spi_device*) ; 
 int /*<<< orphan*/  mchp23k256_write ; 
 int mtd_device_register (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_of_node (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* of_device_get_match_data (TYPE_3__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mchp23k256_flash*) ; 

__attribute__((used)) static int mchp23k256_probe(struct spi_device *spi)
{
	struct mchp23k256_flash *flash;
	struct flash_platform_data *data;
	int err;

	flash = devm_kzalloc(&spi->dev, sizeof(*flash), GFP_KERNEL);
	if (!flash)
		return -ENOMEM;

	flash->spi = spi;
	mutex_init(&flash->lock);
	spi_set_drvdata(spi, flash);

	err = mchp23k256_set_mode(spi);
	if (err)
		return err;

	data = dev_get_platdata(&spi->dev);

	flash->caps = of_device_get_match_data(&spi->dev);
	if (!flash->caps)
		flash->caps = &mchp23k256_caps;

	mtd_set_of_node(&flash->mtd, spi->dev.of_node);
	flash->mtd.dev.parent	= &spi->dev;
	flash->mtd.type		= MTD_RAM;
	flash->mtd.flags	= MTD_CAP_RAM;
	flash->mtd.writesize	= 1;
	flash->mtd.size		= flash->caps->size;
	flash->mtd._read	= mchp23k256_read;
	flash->mtd._write	= mchp23k256_write;

	err = mtd_device_register(&flash->mtd, data ? data->parts : NULL,
				  data ? data->nr_parts : 0);
	if (err)
		return err;

	return 0;
}