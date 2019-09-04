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
struct mtd_info {scalar_t__ erasesize; } ;
struct spi_nor {int /*<<< orphan*/  erase_opcode; struct mtd_info mtd; } ;
struct flash_info {scalar_t__ sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_SE ; 

__attribute__((used)) static int spi_nor_select_erase(struct spi_nor *nor,
				const struct flash_info *info)
{
	struct mtd_info *mtd = &nor->mtd;

	/* Do nothing if already configured from SFDP. */
	if (mtd->erasesize)
		return 0;

#ifdef CONFIG_MTD_SPI_NOR_USE_4K_SECTORS
	/* prefer "small sector" erase if possible */
	if (info->flags & SECT_4K) {
		nor->erase_opcode = SPINOR_OP_BE_4K;
		mtd->erasesize = 4096;
	} else if (info->flags & SECT_4K_PMC) {
		nor->erase_opcode = SPINOR_OP_BE_4K_PMC;
		mtd->erasesize = 4096;
	} else
#endif
	{
		nor->erase_opcode = SPINOR_OP_SE;
		mtd->erasesize = info->sector_size;
	}
	return 0;
}