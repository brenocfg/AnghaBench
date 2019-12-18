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
struct mpc5121_nfc_prv {int csreg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int ads5121_chipselect_init(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	struct device_node *dn;

	dn = of_find_compatible_node(NULL, NULL, "fsl,mpc5121ads-cpld");
	if (dn) {
		prv->csreg = of_iomap(dn, 0);
		of_node_put(dn);
		if (!prv->csreg)
			return -ENOMEM;

		/* CPLD Register 9 controls NAND /CE Lines */
		prv->csreg += 9;
		return 0;
	}

	return -EINVAL;
}