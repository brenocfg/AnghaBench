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
struct qcom_nand_host {scalar_t__ bbm_size; } ;
struct nand_ecc_ctrl {int steps; int bytes; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct mtd_oob_region {int length; scalar_t__ offset; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 

__attribute__((used)) static int qcom_nand_ooblayout_free(struct mtd_info *mtd, int section,
				     struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	if (section)
		return -ERANGE;

	oobregion->length = ecc->steps * 4;
	oobregion->offset = ((ecc->steps - 1) * ecc->bytes) + host->bbm_size;

	return 0;
}