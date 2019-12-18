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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int strength; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int micron_nand_on_die_ecc_setup (struct nand_chip*,int) ; 
 int micron_nand_on_die_ecc_status_4 (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int micron_nand_on_die_ecc_status_8 (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int nand_exit_status_op (struct nand_chip*) ; 
 int nand_read_data_op (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_status_op (struct nand_chip*,int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int
micron_nand_read_page_on_die_ecc(struct nand_chip *chip, uint8_t *buf,
				 int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 status;
	int ret, max_bitflips = 0;

	ret = micron_nand_on_die_ecc_setup(chip, true);
	if (ret)
		return ret;

	ret = nand_read_page_op(chip, page, 0, NULL, 0);
	if (ret)
		goto out;

	ret = nand_status_op(chip, &status);
	if (ret)
		goto out;

	ret = nand_exit_status_op(chip);
	if (ret)
		goto out;

	ret = nand_read_data_op(chip, buf, mtd->writesize, false);
	if (!ret && oob_required)
		ret = nand_read_data_op(chip, chip->oob_poi, mtd->oobsize,
					false);

	if (chip->ecc.strength == 4)
		max_bitflips = micron_nand_on_die_ecc_status_4(chip, status,
							       buf, page,
							       oob_required);
	else
		max_bitflips = micron_nand_on_die_ecc_status_8(chip, status);

out:
	micron_nand_on_die_ecc_setup(chip, false);

	return ret ? ret : max_bitflips;
}