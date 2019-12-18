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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct nand_chip {int page_shift; scalar_t__ oob_poi; } ;
struct mtd_info {int writesize; } ;
struct brcmnand_host {int dummy; } ;

/* Variables and functions */
 int FC_SHIFT ; 
 int /*<<< orphan*/  brcmnand_read (struct mtd_info*,struct nand_chip*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmnand_set_ecc_enabled (struct brcmnand_host*,int) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_read_oob_raw(struct nand_chip *chip, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct brcmnand_host *host = nand_get_controller_data(chip);

	brcmnand_set_ecc_enabled(host, 0);
	brcmnand_read(mtd, chip, (u64)page << chip->page_shift,
		mtd->writesize >> FC_SHIFT,
		NULL, (u8 *)chip->oob_poi);
	brcmnand_set_ecc_enabled(host, 1);
	return 0;
}