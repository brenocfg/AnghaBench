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
typedef  unsigned int u32 ;
struct spi_nor_erase_type {scalar_t__ size; int /*<<< orphan*/  opcode; } ;
struct spi_nor_erase_map {struct spi_nor_erase_type* erase_type; } ;
struct mtd_info {scalar_t__ erasesize; } ;
struct TYPE_3__ {struct spi_nor_erase_map erase_map; } ;
struct spi_nor {int /*<<< orphan*/  erase_opcode; TYPE_2__* info; struct mtd_info mtd; TYPE_1__ params; } ;
struct TYPE_4__ {unsigned int sector_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNOR_ERASE_TYPE_MAX ; 
 scalar_t__ spi_nor_has_uniform_erase (struct spi_nor*) ; 
 struct spi_nor_erase_type* spi_nor_select_uniform_erase (struct spi_nor_erase_map*,unsigned int) ; 

__attribute__((used)) static int spi_nor_select_erase(struct spi_nor *nor)
{
	struct spi_nor_erase_map *map = &nor->params.erase_map;
	const struct spi_nor_erase_type *erase = NULL;
	struct mtd_info *mtd = &nor->mtd;
	u32 wanted_size = nor->info->sector_size;
	int i;

	/*
	 * The previous implementation handling Sector Erase commands assumed
	 * that the SPI flash memory has an uniform layout then used only one
	 * of the supported erase sizes for all Sector Erase commands.
	 * So to be backward compatible, the new implementation also tries to
	 * manage the SPI flash memory as uniform with a single erase sector
	 * size, when possible.
	 */
#ifdef CONFIG_MTD_SPI_NOR_USE_4K_SECTORS
	/* prefer "small sector" erase if possible */
	wanted_size = 4096u;
#endif

	if (spi_nor_has_uniform_erase(nor)) {
		erase = spi_nor_select_uniform_erase(map, wanted_size);
		if (!erase)
			return -EINVAL;
		nor->erase_opcode = erase->opcode;
		mtd->erasesize = erase->size;
		return 0;
	}

	/*
	 * For non-uniform SPI flash memory, set mtd->erasesize to the
	 * maximum erase sector size. No need to set nor->erase_opcode.
	 */
	for (i = SNOR_ERASE_TYPE_MAX - 1; i >= 0; i--) {
		if (map->erase_type[i].size) {
			erase = &map->erase_type[i];
			break;
		}
	}

	if (!erase)
		return -EINVAL;

	mtd->erasesize = erase->size;
	return 0;
}