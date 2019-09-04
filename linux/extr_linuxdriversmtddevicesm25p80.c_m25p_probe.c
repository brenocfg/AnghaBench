#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_hwcaps {int mask; } ;
struct TYPE_4__ {scalar_t__ name; } ;
struct spi_nor {TYPE_1__ mtd; struct m25p* priv; TYPE_2__* dev; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct spi_mem {struct spi_device* spi; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {int mode; char* modalias; TYPE_2__ dev; } ;
struct m25p {struct spi_mem* spimem; struct spi_nor spi_nor; } ;
struct flash_platform_data {char* type; int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; scalar_t__ name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNOR_HWCAPS_PP ; 
 int SNOR_HWCAPS_PP_1_1_4 ; 
 int SNOR_HWCAPS_PP_1_4_4 ; 
 int SNOR_HWCAPS_READ ; 
 int SNOR_HWCAPS_READ_1_1_2 ; 
 int SNOR_HWCAPS_READ_1_1_4 ; 
 int SNOR_HWCAPS_READ_1_2_2 ; 
 int SNOR_HWCAPS_READ_1_4_4 ; 
 int SNOR_HWCAPS_READ_FAST ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 struct flash_platform_data* dev_get_platdata (TYPE_2__*) ; 
 struct m25p* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m25p80_read ; 
 int /*<<< orphan*/  m25p80_read_reg ; 
 int /*<<< orphan*/  m25p80_write ; 
 int /*<<< orphan*/  m25p80_write_reg ; 
 int mtd_device_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spi_mem_get_name (struct spi_mem*) ; 
 int /*<<< orphan*/  spi_mem_set_drvdata (struct spi_mem*,struct m25p*) ; 
 int spi_nor_scan (struct spi_nor*,char*,struct spi_nor_hwcaps*) ; 
 int /*<<< orphan*/  spi_nor_set_flash_node (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int m25p_probe(struct spi_mem *spimem)
{
	struct spi_device *spi = spimem->spi;
	struct flash_platform_data	*data;
	struct m25p *flash;
	struct spi_nor *nor;
	struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	};
	char *flash_name;
	int ret;

	data = dev_get_platdata(&spimem->spi->dev);

	flash = devm_kzalloc(&spimem->spi->dev, sizeof(*flash), GFP_KERNEL);
	if (!flash)
		return -ENOMEM;

	nor = &flash->spi_nor;

	/* install the hooks */
	nor->read = m25p80_read;
	nor->write = m25p80_write;
	nor->write_reg = m25p80_write_reg;
	nor->read_reg = m25p80_read_reg;

	nor->dev = &spimem->spi->dev;
	spi_nor_set_flash_node(nor, spi->dev.of_node);
	nor->priv = flash;

	spi_mem_set_drvdata(spimem, flash);
	flash->spimem = spimem;

	if (spi->mode & SPI_RX_QUAD) {
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;

		if (spi->mode & SPI_TX_QUAD)
			hwcaps.mask |= (SNOR_HWCAPS_READ_1_4_4 |
					SNOR_HWCAPS_PP_1_1_4 |
					SNOR_HWCAPS_PP_1_4_4);
	} else if (spi->mode & SPI_RX_DUAL) {
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;

		if (spi->mode & SPI_TX_DUAL)
			hwcaps.mask |= SNOR_HWCAPS_READ_1_2_2;
	}

	if (data && data->name)
		nor->mtd.name = data->name;

	if (!nor->mtd.name)
		nor->mtd.name = spi_mem_get_name(spimem);

	/* For some (historical?) reason many platforms provide two different
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

	return mtd_device_register(&nor->mtd, data ? data->parts : NULL,
				   data ? data->nr_parts : 0);
}