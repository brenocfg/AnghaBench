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
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int tegra_nand_page_xfer (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tegra_nand_read_page_raw(struct nand_chip *chip, u8 *buf,
				    int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	void *oob_buf = oob_required ? chip->oob_poi : NULL;

	return tegra_nand_page_xfer(mtd, chip, buf, oob_buf,
				    mtd->oobsize, page, true);
}