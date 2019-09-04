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
struct nand_ecc_ctrl {int mode; int /*<<< orphan*/  strength; scalar_t__ size; } ;
struct nand_chip {int bbt_options; int options; int /*<<< orphan*/  ecc_strength_ds; scalar_t__ ecc_step_ds; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
#define  NAND_ECC_HW 130 
#define  NAND_ECC_NONE 129 
#define  NAND_ECC_SOFT 128 
 int NAND_NEED_SCRAMBLING ; 
 int NAND_NO_SUBPAGE_WRITE ; 
 int NAND_SUBPAGE_READ ; 
 struct device_node* nand_get_flash_node (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int sunxi_nand_hw_ecc_ctrl_init (struct mtd_info*,struct nand_ecc_ctrl*,struct device_node*) ; 

__attribute__((used)) static int sunxi_nand_attach_chip(struct nand_chip *nand)
{
	struct mtd_info *mtd = nand_to_mtd(nand);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	struct device_node *np = nand_get_flash_node(nand);
	int ret;

	if (nand->bbt_options & NAND_BBT_USE_FLASH)
		nand->bbt_options |= NAND_BBT_NO_OOB;

	if (nand->options & NAND_NEED_SCRAMBLING)
		nand->options |= NAND_NO_SUBPAGE_WRITE;

	nand->options |= NAND_SUBPAGE_READ;

	if (!ecc->size) {
		ecc->size = nand->ecc_step_ds;
		ecc->strength = nand->ecc_strength_ds;
	}

	if (!ecc->size || !ecc->strength)
		return -EINVAL;

	switch (ecc->mode) {
	case NAND_ECC_HW:
		ret = sunxi_nand_hw_ecc_ctrl_init(mtd, ecc, np);
		if (ret)
			return ret;
		break;
	case NAND_ECC_NONE:
	case NAND_ECC_SOFT:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}