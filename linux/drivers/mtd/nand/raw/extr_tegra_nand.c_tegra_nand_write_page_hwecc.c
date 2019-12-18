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
struct tegra_nand_controller {int dummy; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  controller; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  tegra_nand_hw_ecc (struct tegra_nand_controller*,struct nand_chip*,int) ; 
 int tegra_nand_page_xfer (struct mtd_info*,struct nand_chip*,void*,void*,int /*<<< orphan*/ ,int,int) ; 
 struct tegra_nand_controller* to_tegra_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_nand_write_page_hwecc(struct nand_chip *chip, const u8 *buf,
				       int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	void *oob_buf = oob_required ? chip->oob_poi : NULL;
	int ret;

	tegra_nand_hw_ecc(ctrl, chip, true);
	ret = tegra_nand_page_xfer(mtd, chip, (void *)buf, oob_buf,
				   0, page, false);
	tegra_nand_hw_ecc(ctrl, chip, false);

	return ret;
}