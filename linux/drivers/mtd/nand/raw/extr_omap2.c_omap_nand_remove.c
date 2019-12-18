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
struct platform_device {int dummy; } ;
struct omap_nand_info {scalar_t__ dma; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priv; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_bch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_release (struct nand_chip*) ; 
 struct mtd_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int omap_nand_remove(struct platform_device *pdev)
{
	struct mtd_info *mtd = platform_get_drvdata(pdev);
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct omap_nand_info *info = mtd_to_omap(mtd);
	if (nand_chip->ecc.priv) {
		nand_bch_free(nand_chip->ecc.priv);
		nand_chip->ecc.priv = NULL;
	}
	if (info->dma)
		dma_release_channel(info->dma);
	nand_release(nand_chip);
	return 0;
}