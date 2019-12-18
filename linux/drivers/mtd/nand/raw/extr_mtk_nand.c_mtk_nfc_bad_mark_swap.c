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
typedef  size_t u32 ;
struct TYPE_3__ {size_t size; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; TYPE_1__ ecc; } ;
struct TYPE_4__ {size_t pos; size_t sec; } ;
struct mtk_nfc_nand_chip {TYPE_2__ bad_mark; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 size_t mtk_data_len (struct nand_chip*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static void mtk_nfc_bad_mark_swap(struct mtd_info *mtd, u8 *buf, int raw)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtk_nfc_nand_chip *nand = to_mtk_nand(chip);
	u32 bad_pos = nand->bad_mark.pos;

	if (raw)
		bad_pos += nand->bad_mark.sec * mtk_data_len(chip);
	else
		bad_pos += nand->bad_mark.sec * chip->ecc.size;

	swap(chip->oob_poi[0], buf[bad_pos]);
}