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
struct TYPE_4__ {int size; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_2__ ecc; } ;
struct mtd_info {int writesize; } ;
struct lpc32xx_nand_host {int mlcsubpages; void* dummy_buf; void* dma_buf; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_ooblayout_ops ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int lpc32xx_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	struct device *dev = &host->pdev->dev;

	host->dma_buf = devm_kzalloc(dev, mtd->writesize, GFP_KERNEL);
	if (!host->dma_buf)
		return -ENOMEM;

	host->dummy_buf = devm_kzalloc(dev, mtd->writesize, GFP_KERNEL);
	if (!host->dummy_buf)
		return -ENOMEM;

	chip->ecc.mode = NAND_ECC_HW;
	chip->ecc.size = 512;
	mtd_set_ooblayout(mtd, &lpc32xx_ooblayout_ops);
	host->mlcsubpages = mtd->writesize / 512;

	return 0;
}