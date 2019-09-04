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
struct nand_chip {int dummy; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int dummy; } ;
struct brcmnand_cfg {int spare_area_size; int sector_size_1k; int page_size; } ;
struct brcmnand_host {struct brcmnand_cfg hwcfg; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_hamming_ooblayout_free(struct mtd_info *mtd, int section,
					   struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_cfg *cfg = &host->hwcfg;
	int sas = cfg->spare_area_size << cfg->sector_size_1k;
	int sectors = cfg->page_size / (512 << cfg->sector_size_1k);

	if (section >= sectors * 2)
		return -ERANGE;

	oobregion->offset = (section / 2) * sas;

	if (section & 1) {
		oobregion->offset += 9;
		oobregion->length = 7;
	} else {
		oobregion->length = 6;

		/* First sector of each page may have BBI */
		if (!section) {
			/*
			 * Small-page NAND use byte 6 for BBI while large-page
			 * NAND use byte 0.
			 */
			if (cfg->page_size > 512)
				oobregion->offset++;
			oobregion->length--;
		}
	}

	return 0;
}