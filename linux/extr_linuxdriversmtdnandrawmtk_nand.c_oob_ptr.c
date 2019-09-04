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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct TYPE_3__ {int reg_size; } ;
struct TYPE_4__ {int sec; } ;
struct mtk_nfc_nand_chip {TYPE_1__ fdm; TYPE_2__ bad_mark; } ;

/* Variables and functions */
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static inline u8 *oob_ptr(struct nand_chip *chip, int i)
{
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u8 *poi;

	/* map the sector's FDM data to free oob:
	 * the beginning of the oob area stores the FDM data of bad mark sectors
	 */

	if (i < mtk_nand->bad_mark.sec)
		poi = chip->oob_poi + (i + 1) * mtk_nand->fdm.reg_size;
	else if (i == mtk_nand->bad_mark.sec)
		poi = chip->oob_poi;
	else
		poi = chip->oob_poi + i * mtk_nand->fdm.reg_size;

	return poi;
}