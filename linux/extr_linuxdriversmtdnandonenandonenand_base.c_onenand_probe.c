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
struct onenand_chip {int (* chip_probe ) (struct mtd_info*) ;int (* read_word ) (scalar_t__) ;int technology; int device_id; int version_id; int dies; int chipsize; int erase_shift; int page_shift; int page_mask; int density_mask; int writesize; scalar_t__ base; } ;
struct mtd_info {int numeraseregions; int writesize; int oobsize; int erasesize; int size; int /*<<< orphan*/  eraseregions; struct onenand_chip* priv; } ;
struct mtd_erase_region_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FLEXONENAND (struct onenand_chip*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ONENAND_IS_2PLANE (struct onenand_chip*) ; 
 scalar_t__ ONENAND_IS_4KB_PAGE (struct onenand_chip*) ; 
 scalar_t__ ONENAND_IS_DDP (struct onenand_chip*) ; 
 scalar_t__ ONENAND_REG_DATA_BUFFER_SIZE ; 
 scalar_t__ ONENAND_REG_DEVICE_ID ; 
 scalar_t__ ONENAND_REG_TECHNOLOGY ; 
 scalar_t__ ONENAND_REG_VERSION_ID ; 
 void* ffs (int) ; 
 int /*<<< orphan*/  flexonenand_get_size (struct mtd_info*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onenand_check_features (struct mtd_info*) ; 
 int onenand_get_density (int) ; 
 int /*<<< orphan*/  onenand_print_device_info (int,int) ; 
 int stub1 (struct mtd_info*) ; 
 int stub2 (scalar_t__) ; 
 int stub3 (scalar_t__) ; 
 int stub4 (scalar_t__) ; 
 int stub5 (scalar_t__) ; 

__attribute__((used)) static int onenand_probe(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	int dev_id, ver_id;
	int density;
	int ret;

	ret = this->chip_probe(mtd);
	if (ret)
		return ret;

	/* Device and version IDs from Register */
	dev_id = this->read_word(this->base + ONENAND_REG_DEVICE_ID);
	ver_id = this->read_word(this->base + ONENAND_REG_VERSION_ID);
	this->technology = this->read_word(this->base + ONENAND_REG_TECHNOLOGY);

	/* Flash device information */
	onenand_print_device_info(dev_id, ver_id);
	this->device_id = dev_id;
	this->version_id = ver_id;

	/* Check OneNAND features */
	onenand_check_features(mtd);

	density = onenand_get_density(dev_id);
	if (FLEXONENAND(this)) {
		this->dies = ONENAND_IS_DDP(this) ? 2 : 1;
		/* Maximum possible erase regions */
		mtd->numeraseregions = this->dies << 1;
		mtd->eraseregions =
			kcalloc(this->dies << 1,
				sizeof(struct mtd_erase_region_info),
				GFP_KERNEL);
		if (!mtd->eraseregions)
			return -ENOMEM;
	}

	/*
	 * For Flex-OneNAND, chipsize represents maximum possible device size.
	 * mtd->size represents the actual device size.
	 */
	this->chipsize = (16 << density) << 20;

	/* OneNAND page size & block size */
	/* The data buffer size is equal to page size */
	mtd->writesize = this->read_word(this->base + ONENAND_REG_DATA_BUFFER_SIZE);
	/* We use the full BufferRAM */
	if (ONENAND_IS_4KB_PAGE(this))
		mtd->writesize <<= 1;

	mtd->oobsize = mtd->writesize >> 5;
	/* Pages per a block are always 64 in OneNAND */
	mtd->erasesize = mtd->writesize << 6;
	/*
	 * Flex-OneNAND SLC area has 64 pages per block.
	 * Flex-OneNAND MLC area has 128 pages per block.
	 * Expose MLC erase size to find erase_shift and page_mask.
	 */
	if (FLEXONENAND(this))
		mtd->erasesize <<= 1;

	this->erase_shift = ffs(mtd->erasesize) - 1;
	this->page_shift = ffs(mtd->writesize) - 1;
	this->page_mask = (1 << (this->erase_shift - this->page_shift)) - 1;
	/* Set density mask. it is used for DDP */
	if (ONENAND_IS_DDP(this))
		this->density_mask = this->chipsize >> (this->erase_shift + 1);
	/* It's real page size */
	this->writesize = mtd->writesize;

	/* REVISIT: Multichip handling */

	if (FLEXONENAND(this))
		flexonenand_get_size(mtd);
	else
		mtd->size = this->chipsize;

	/*
	 * We emulate the 4KiB page and 256KiB erase block size
	 * But oobsize is still 64 bytes.
	 * It is only valid if you turn on 2X program support,
	 * Otherwise it will be ignored by compiler.
	 */
	if (ONENAND_IS_2PLANE(this)) {
		mtd->writesize <<= 1;
		mtd->erasesize <<= 1;
	}

	return 0;
}