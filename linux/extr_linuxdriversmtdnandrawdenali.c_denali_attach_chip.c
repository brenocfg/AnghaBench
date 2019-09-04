#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int strength; int /*<<< orphan*/  write_oob; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  read_page; int /*<<< orphan*/  bytes; int /*<<< orphan*/  mode; } ;
struct nand_chip {int options; int buf_align; int /*<<< orphan*/  erase; TYPE_1__ ecc; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  bbt_options; } ;
struct mtd_info {int oobsize; int erasesize; int writesize; } ;
struct denali_nand_info {int dma_avail; int caps; int /*<<< orphan*/  buf; scalar_t__ reg; int /*<<< orphan*/  dev; scalar_t__ oob_skip_bytes; int /*<<< orphan*/  ecc_caps; int /*<<< orphan*/  setup_dma; } ;

/* Variables and functions */
 scalar_t__ CFG_DATA_BLOCK_SIZE ; 
 scalar_t__ CFG_LAST_DATA_BLOCK_SIZE ; 
 scalar_t__ CFG_NUM_DATA_BLOCKS ; 
 int DENALI_CAP_DMA_64BIT ; 
 scalar_t__ DEVICE_MAIN_AREA_SIZE ; 
 scalar_t__ DEVICE_SPARE_AREA_SIZE ; 
 scalar_t__ DEVICE_WIDTH ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ ECC_CORRECTION ; 
 int /*<<< orphan*/  ECC_CORRECTION__ERASE_THRESHOLD ; 
 int /*<<< orphan*/  ECC_CORRECTION__VALUE ; 
 int ENOMEM ; 
 scalar_t__ FEATURES ; 
 int FEATURES__DMA ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_BBT_NO_OOB ; 
 int /*<<< orphan*/  NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_HW_SYNDROME ; 
 int NAND_NO_SUBPAGE_WRITE ; 
 int NAND_ROW_ADDR_3 ; 
 int NAND_USE_BOUNCE_BUFFER ; 
 scalar_t__ PAGES_PER_BLOCK ; 
 scalar_t__ TWO_ROW_ADDR_CYCLES ; 
 int TWO_ROW_ADDR_CYCLES__FLAG ; 
 int /*<<< orphan*/  denali_erase ; 
 int denali_multidev_fixup (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_ooblayout_ops ; 
 int /*<<< orphan*/  denali_read_buf ; 
 int /*<<< orphan*/  denali_read_buf16 ; 
 int /*<<< orphan*/  denali_read_oob ; 
 int /*<<< orphan*/  denali_read_page ; 
 int /*<<< orphan*/  denali_read_page_raw ; 
 int /*<<< orphan*/  denali_setup_dma32 ; 
 int /*<<< orphan*/  denali_setup_dma64 ; 
 int /*<<< orphan*/  denali_write_buf ; 
 int /*<<< orphan*/  denali_write_buf16 ; 
 int /*<<< orphan*/  denali_write_oob ; 
 int /*<<< orphan*/  denali_write_page ; 
 int /*<<< orphan*/  denali_write_page_raw ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int dma_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int nand_ecc_choose_conf (struct nand_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int denali_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	int ret;

	if (ioread32(denali->reg + FEATURES) & FEATURES__DMA)
		denali->dma_avail = 1;

	if (denali->dma_avail) {
		int dma_bit = denali->caps & DENALI_CAP_DMA_64BIT ? 64 : 32;

		ret = dma_set_mask(denali->dev, DMA_BIT_MASK(dma_bit));
		if (ret) {
			dev_info(denali->dev,
				 "Failed to set DMA mask. Disabling DMA.\n");
			denali->dma_avail = 0;
		}
	}

	if (denali->dma_avail) {
		chip->options |= NAND_USE_BOUNCE_BUFFER;
		chip->buf_align = 16;
		if (denali->caps & DENALI_CAP_DMA_64BIT)
			denali->setup_dma = denali_setup_dma64;
		else
			denali->setup_dma = denali_setup_dma32;
	}

	chip->bbt_options |= NAND_BBT_USE_FLASH;
	chip->bbt_options |= NAND_BBT_NO_OOB;
	chip->ecc.mode = NAND_ECC_HW_SYNDROME;
	chip->options |= NAND_NO_SUBPAGE_WRITE;

	ret = nand_ecc_choose_conf(chip, denali->ecc_caps,
				   mtd->oobsize - denali->oob_skip_bytes);
	if (ret) {
		dev_err(denali->dev, "Failed to setup ECC settings.\n");
		return ret;
	}

	dev_dbg(denali->dev,
		"chosen ECC settings: step=%d, strength=%d, bytes=%d\n",
		chip->ecc.size, chip->ecc.strength, chip->ecc.bytes);

	iowrite32(FIELD_PREP(ECC_CORRECTION__ERASE_THRESHOLD, 1) |
		  FIELD_PREP(ECC_CORRECTION__VALUE, chip->ecc.strength),
		  denali->reg + ECC_CORRECTION);
	iowrite32(mtd->erasesize / mtd->writesize,
		  denali->reg + PAGES_PER_BLOCK);
	iowrite32(chip->options & NAND_BUSWIDTH_16 ? 1 : 0,
		  denali->reg + DEVICE_WIDTH);
	iowrite32(chip->options & NAND_ROW_ADDR_3 ? 0 : TWO_ROW_ADDR_CYCLES__FLAG,
		  denali->reg + TWO_ROW_ADDR_CYCLES);
	iowrite32(mtd->writesize, denali->reg + DEVICE_MAIN_AREA_SIZE);
	iowrite32(mtd->oobsize, denali->reg + DEVICE_SPARE_AREA_SIZE);

	iowrite32(chip->ecc.size, denali->reg + CFG_DATA_BLOCK_SIZE);
	iowrite32(chip->ecc.size, denali->reg + CFG_LAST_DATA_BLOCK_SIZE);
	/* chip->ecc.steps is set by nand_scan_tail(); not available here */
	iowrite32(mtd->writesize / chip->ecc.size,
		  denali->reg + CFG_NUM_DATA_BLOCKS);

	mtd_set_ooblayout(mtd, &denali_ooblayout_ops);

	if (chip->options & NAND_BUSWIDTH_16) {
		chip->read_buf = denali_read_buf16;
		chip->write_buf = denali_write_buf16;
	} else {
		chip->read_buf = denali_read_buf;
		chip->write_buf = denali_write_buf;
	}
	chip->ecc.read_page = denali_read_page;
	chip->ecc.read_page_raw = denali_read_page_raw;
	chip->ecc.write_page = denali_write_page;
	chip->ecc.write_page_raw = denali_write_page_raw;
	chip->ecc.read_oob = denali_read_oob;
	chip->ecc.write_oob = denali_write_oob;
	chip->erase = denali_erase;

	ret = denali_multidev_fixup(denali);
	if (ret)
		return ret;

	/*
	 * This buffer is DMA-mapped by denali_{read,write}_page_raw.  Do not
	 * use devm_kmalloc() because the memory allocated by devm_ does not
	 * guarantee DMA-safe alignment.
	 */
	denali->buf = kmalloc(mtd->writesize + mtd->oobsize, GFP_KERNEL);
	if (!denali->buf)
		return -ENOMEM;

	return 0;
}