#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int dummy; } ;
struct mtd_info {int writesize; } ;
struct TYPE_4__ {int size; int bytes; int strength; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  read_page; int /*<<< orphan*/  write_oob; int /*<<< orphan*/  write_page; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {TYPE_1__ ecc; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; } ;
struct cafe_priv {int /*<<< orphan*/  dmaaddr; int /*<<< orphan*/  dmabuf; TYPE_3__* pdev; TYPE_2__ nand; int /*<<< orphan*/  ctl2; int /*<<< orphan*/  usedma; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_DMA_ADDR0 ; 
 int /*<<< orphan*/  NAND_DMA_ADDR1 ; 
 int /*<<< orphan*/  NAND_ECC_HW_SYNDROME ; 
 int /*<<< orphan*/  cafe_bbt_main_descr_2048 ; 
 int /*<<< orphan*/  cafe_bbt_main_descr_512 ; 
 int /*<<< orphan*/  cafe_bbt_mirror_descr_2048 ; 
 int /*<<< orphan*/  cafe_bbt_mirror_descr_512 ; 
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_nand_read_oob ; 
 int /*<<< orphan*/  cafe_nand_read_page ; 
 int /*<<< orphan*/  cafe_nand_write_oob ; 
 int /*<<< orphan*/  cafe_nand_write_page_lowlevel ; 
 int /*<<< orphan*/  cafe_ooblayout_ops ; 
 int /*<<< orphan*/  cafe_readl (struct cafe_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_writel (struct cafe_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct cafe_priv* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usedma ; 

__attribute__((used)) static int cafe_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct cafe_priv *cafe = nand_get_controller_data(chip);
	int err = 0;

	cafe->dmabuf = dma_alloc_coherent(&cafe->pdev->dev, 2112,
					  &cafe->dmaaddr, GFP_KERNEL);
	if (!cafe->dmabuf)
		return -ENOMEM;

	/* Set up DMA address */
	cafe_writel(cafe, lower_32_bits(cafe->dmaaddr), NAND_DMA_ADDR0);
	cafe_writel(cafe, upper_32_bits(cafe->dmaaddr), NAND_DMA_ADDR1);

	cafe_dev_dbg(&cafe->pdev->dev, "Set DMA address to %x (virt %p)\n",
		     cafe_readl(cafe, NAND_DMA_ADDR0), cafe->dmabuf);

	/* Restore the DMA flag */
	cafe->usedma = usedma;

	cafe->ctl2 = BIT(27); /* Reed-Solomon ECC */
	if (mtd->writesize == 2048)
		cafe->ctl2 |= BIT(29); /* 2KiB page size */

	/* Set up ECC according to the type of chip we found */
	mtd_set_ooblayout(mtd, &cafe_ooblayout_ops);
	if (mtd->writesize == 2048) {
		cafe->nand.bbt_td = &cafe_bbt_main_descr_2048;
		cafe->nand.bbt_md = &cafe_bbt_mirror_descr_2048;
	} else if (mtd->writesize == 512) {
		cafe->nand.bbt_td = &cafe_bbt_main_descr_512;
		cafe->nand.bbt_md = &cafe_bbt_mirror_descr_512;
	} else {
		dev_warn(&cafe->pdev->dev,
			 "Unexpected NAND flash writesize %d. Aborting\n",
			 mtd->writesize);
		err = -ENOTSUPP;
		goto out_free_dma;
	}

	cafe->nand.ecc.mode = NAND_ECC_HW_SYNDROME;
	cafe->nand.ecc.size = mtd->writesize;
	cafe->nand.ecc.bytes = 14;
	cafe->nand.ecc.strength = 4;
	cafe->nand.ecc.write_page = cafe_nand_write_page_lowlevel;
	cafe->nand.ecc.write_oob = cafe_nand_write_oob;
	cafe->nand.ecc.read_page = cafe_nand_read_page;
	cafe->nand.ecc.read_oob = cafe_nand_read_oob;

	return 0;

 out_free_dma:
	dma_free_coherent(&cafe->pdev->dev, 2112, cafe->dmabuf, cafe->dmaaddr);

	return err;
}