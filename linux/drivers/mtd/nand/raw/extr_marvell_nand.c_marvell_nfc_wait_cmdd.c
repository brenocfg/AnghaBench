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
struct nand_chip {int dummy; } ;
struct marvell_nand_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndcb0_csel; } ;

/* Variables and functions */
 int NDSR_CMDD (int /*<<< orphan*/ ) ; 
 int marvell_nfc_end_cmd (struct nand_chip*,int,char*) ; 
 struct marvell_nand_chip* to_marvell_nand (struct nand_chip*) ; 
 TYPE_1__* to_nand_sel (struct marvell_nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_wait_cmdd(struct nand_chip *chip)
{
	struct marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	int cs_flag = NDSR_CMDD(to_nand_sel(marvell_nand)->ndcb0_csel);

	return marvell_nfc_end_cmd(chip, cs_flag, "CMDD");
}