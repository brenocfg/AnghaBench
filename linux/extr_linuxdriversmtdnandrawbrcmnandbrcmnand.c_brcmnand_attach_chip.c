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
struct TYPE_3__ {int size; } ;
struct nand_chip {int bbt_options; TYPE_1__ ecc; int /*<<< orphan*/  options; } ;
struct mtd_info {int bitflip_threshold; } ;
struct TYPE_4__ {scalar_t__ sector_size_1k; } ;
struct brcmnand_host {TYPE_2__ hwcfg; } ;

/* Variables and functions */
 int ENXIO ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int /*<<< orphan*/  NAND_USE_BOUNCE_BUFFER ; 
 scalar_t__ brcmnand_setup_dev (struct brcmnand_host*) ; 
 int brcmstb_choose_ecc_layout (struct brcmnand_host*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	int ret;

	chip->options |= NAND_NO_SUBPAGE_WRITE;
	/*
	 * Avoid (for instance) kmap()'d buffers from JFFS2, which we can't DMA
	 * to/from, and have nand_base pass us a bounce buffer instead, as
	 * needed.
	 */
	chip->options |= NAND_USE_BOUNCE_BUFFER;

	if (chip->bbt_options & NAND_BBT_USE_FLASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	if (brcmnand_setup_dev(host))
		return -ENXIO;

	chip->ecc.size = host->hwcfg.sector_size_1k ? 1024 : 512;

	/* only use our internal HW threshold */
	mtd->bitflip_threshold = 1;

	ret = brcmstb_choose_ecc_layout(host);

	return ret;
}