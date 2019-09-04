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
struct mpc5121_nfc_prv {scalar_t__ csreg; scalar_t__ clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void mpc5121_nfc_free(struct device *dev, struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	if (prv->clk)
		clk_disable_unprepare(prv->clk);

	if (prv->csreg)
		iounmap(prv->csreg);
}