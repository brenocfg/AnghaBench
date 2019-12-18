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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int NFC_ACTIVE_CS_MASK ; 
 int NFC_ACTIVE_CS_SHIFT ; 
 int /*<<< orphan*/  NFC_BUF_ADDR ; 
 int NFC_CE ; 
 int /*<<< orphan*/  NFC_CONFIG1 ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nfc_clear (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_set (struct mtd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mpc5121_nfc_select_chip(struct nand_chip *nand, int chip)
{
	struct mtd_info *mtd = nand_to_mtd(nand);

	if (chip < 0) {
		nfc_clear(mtd, NFC_CONFIG1, NFC_CE);
		return;
	}

	nfc_clear(mtd, NFC_BUF_ADDR, NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_BUF_ADDR, (chip << NFC_ACTIVE_CS_SHIFT) &
							NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_CONFIG1, NFC_CE);
}