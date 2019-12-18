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
typedef  int u32 ;
struct nand_chip {int pagemask; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc5121_nfc_send_addr (struct mtd_info*,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static void mpc5121_nfc_addr_cycle(struct mtd_info *mtd, int column, int page)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u32 pagemask = chip->pagemask;

	if (column != -1) {
		mpc5121_nfc_send_addr(mtd, column);
		if (mtd->writesize > 512)
			mpc5121_nfc_send_addr(mtd, column >> 8);
	}

	if (page != -1) {
		do {
			mpc5121_nfc_send_addr(mtd, page & 0xFF);
			page >>= 8;
			pagemask >>= 8;
		} while (pagemask);
	}
}