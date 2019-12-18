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
struct TYPE_2__ {int size; int strength; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_subpage; int /*<<< orphan*/  read_page; scalar_t__ bytes; } ;
struct nand_chip {int /*<<< orphan*/  options; TYPE_1__ ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_SUBPAGE_READ ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_ooblayout_lp_ops ; 
 int /*<<< orphan*/  nand_read_page_raw_notsupp ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_write_page_raw ; 
 int /*<<< orphan*/  nand_write_page_raw_notsupp ; 
 int /*<<< orphan*/  toshiba_nand_read_page_benand ; 
 int /*<<< orphan*/  toshiba_nand_read_subpage_benand ; 

__attribute__((used)) static void toshiba_nand_benand_init(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/*
	 * On BENAND, the entire OOB region can be used by the MTD user.
	 * The calculated ECC bytes are stored into other isolated
	 * area which is not accessible to users.
	 * This is why chip->ecc.bytes = 0.
	 */
	chip->ecc.bytes = 0;
	chip->ecc.size = 512;
	chip->ecc.strength = 8;
	chip->ecc.read_page = toshiba_nand_read_page_benand;
	chip->ecc.read_subpage = toshiba_nand_read_subpage_benand;
	chip->ecc.write_page = nand_write_page_raw;
	chip->ecc.read_page_raw = nand_read_page_raw_notsupp;
	chip->ecc.write_page_raw = nand_write_page_raw_notsupp;

	chip->options |= NAND_SUBPAGE_READ;

	mtd_set_ooblayout(mtd, &nand_ooblayout_lp_ops);
}