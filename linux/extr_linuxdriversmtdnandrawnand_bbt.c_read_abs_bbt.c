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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int numchips; int chipsize; int bbt_erase_shift; } ;
struct nand_bbt_descr {int options; int /*<<< orphan*/ * pages; } ;
struct mtd_info {int size; } ;

/* Variables and functions */
 int NAND_BBT_PERCHIP ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int read_bbt (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct nand_bbt_descr*,int) ; 

__attribute__((used)) static int read_abs_bbt(struct mtd_info *mtd, uint8_t *buf, struct nand_bbt_descr *td, int chip)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	int res = 0, i;

	if (td->options & NAND_BBT_PERCHIP) {
		int offs = 0;
		for (i = 0; i < this->numchips; i++) {
			if (chip == -1 || chip == i)
				res = read_bbt(mtd, buf, td->pages[i],
					this->chipsize >> this->bbt_erase_shift,
					td, offs);
			if (res)
				return res;
			offs += this->chipsize >> this->bbt_erase_shift;
		}
	} else {
		res = read_bbt(mtd, buf, td->pages[0],
				mtd->size >> this->bbt_erase_shift, td, 0);
		if (res)
			return res;
	}
	return 0;
}