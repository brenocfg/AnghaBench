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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 int nand_read_oob_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_nand_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
			      int page)
{
	return nand_read_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
}