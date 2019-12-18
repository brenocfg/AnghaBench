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
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mxc_nand_host {int eccsize; TYPE_2__* devtype_data; } ;
struct mtd_info {scalar_t__ writesize; } ;
struct TYPE_4__ {int /*<<< orphan*/  irqpending_quirk; } ;

/* Variables and functions */
 scalar_t__ NAND_ECC_HW ; 
 int /*<<< orphan*/  NFC_V1_UNLOCKEND_BLKADDR ; 
 int /*<<< orphan*/  NFC_V1_UNLOCKSTART_BLKADDR ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG1 ; 
 int NFC_V1_V2_CONFIG1_ECC_EN ; 
 int NFC_V1_V2_CONFIG1_INT_MSK ; 
 int /*<<< orphan*/  NFC_V1_V2_WRPROT ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void preset_v1(struct mtd_info *mtd)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uint16_t config1 = 0;

	if (nand_chip->ecc.mode == NAND_ECC_HW && mtd->writesize)
		config1 |= NFC_V1_V2_CONFIG1_ECC_EN;

	if (!host->devtype_data->irqpending_quirk)
		config1 |= NFC_V1_V2_CONFIG1_INT_MSK;

	host->eccsize = 1;

	writew(config1, NFC_V1_V2_CONFIG1);
	/* preset operation */

	/* Unlock the internal RAM Buffer */
	writew(0x2, NFC_V1_V2_CONFIG);

	/* Blocks to be unlocked */
	writew(0x0, NFC_V1_UNLOCKSTART_BLKADDR);
	writew(0xffff, NFC_V1_UNLOCKEND_BLKADDR);

	/* Unlock Block Command for given address range */
	writew(0x4, NFC_V1_V2_WRPROT);
}