#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int /*<<< orphan*/  mask; } ;
struct TYPE_6__ {scalar_t__ name; } ;
struct spi_nor {scalar_t__ page_size; scalar_t__ bouncebuf_size; TYPE_1__ mtd; int /*<<< orphan*/  bouncebuf; TYPE_2__* dev; struct spi_mem* spimem; } ;
struct spi_mem {struct spi_device* spi; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {char* modalias; TYPE_2__ dev; } ;
struct flash_platform_data {char* type; int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; scalar_t__ name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SNOR_HWCAPS_ALL ; 
 struct flash_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_kfree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kmalloc (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct spi_nor* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_mem_get_name (struct spi_mem*) ; 
 int /*<<< orphan*/  spi_mem_set_drvdata (struct spi_mem*,struct spi_nor*) ; 
 int spi_nor_scan (struct spi_nor*,char*,struct spi_nor_hwcaps const*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int spi_nor_probe(struct spi_mem *spimem)
{
	struct spi_device *spi = spimem->spi;
	struct flash_platform_data *data = dev_get_platdata(&spi->dev);
	struct spi_nor *nor;
	/*
	 * Enable all caps by default. The core will mask them after
	 * checking what's really supported using spi_mem_supports_op().
	 */
	const struct spi_nor_hwcaps hwcaps = { .mask = SNOR_HWCAPS_ALL };
	char *flash_name;
	int ret;

	nor = devm_kzalloc(&spi->dev, sizeof(*nor), GFP_KERNEL);
	if (!nor)
		return -ENOMEM;

	nor->spimem = spimem;
	nor->dev = &spi->dev;
	spi_nor_set_flash_node(nor, spi->dev.of_node);

	spi_mem_set_drvdata(spimem, nor);

	if (data && data->name)
		nor->mtd.name = data->name;

	if (!nor->mtd.name)
		nor->mtd.name = spi_mem_get_name(spimem);

	/*
	 * For some (historical?) reason many platforms provide two different
	 * names in flash_platform_data: "name" and "type". Quite often name is
	 * set to "m25p80" and then "type" provides a real chip name.
	 * If that's the case, respect "type" and ignore a "name".
	 */
	if (data && data->type)
		flash_name = data->type;
	else if (!strcmp(spi->modalias, "spi-nor"))
		flash_name = NULL; /* auto-detect */
	else
		flash_name = spi->modalias;

	ret = spi_nor_scan(nor, flash_name, &hwcaps);
	if (ret)
		return ret;

	/*
	 * None of the existing parts have > 512B pages, but let's play safe
	 * and add this logic so that if anyone ever adds support for such
	 * a NOR we don't end up with buffer overflows.
	 */
	if (nor->page_size > PAGE_SIZE) {
		nor->bouncebuf_size = nor->page_size;
		devm_kfree(nor->dev, nor->bouncebuf);
		nor->bouncebuf = devm_kmalloc(nor->dev,
					      nor->bouncebuf_size,
					      GFP_KERNEL);
		if (!nor->bouncebuf)
			return -ENOMEM;
	}

	return mtd_device_register(&nor->mtd, data ? data->parts : NULL,
				   data ? data->nr_parts : 0);
}