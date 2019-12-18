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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct TYPE_2__ {int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_1__ ecc_stats; int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct fsl_lbc_ctrl {struct fsl_elbc_fcm_ctrl* nand; } ;
struct fsl_elbc_mtd {struct fsl_lbc_ctrl* ctrl; } ;
struct fsl_elbc_fcm_ctrl {int max_bitflips; } ;

/* Variables and functions */
 int NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  fsl_elbc_read_buf (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsl_elbc_wait (struct nand_chip*) ; 
 struct fsl_elbc_mtd* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int fsl_elbc_read_page(struct nand_chip *chip, uint8_t *buf,
			      int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_lbc_ctrl *ctrl = priv->ctrl;
	struct fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = ctrl->nand;

	nand_read_page_op(chip, page, 0, buf, mtd->writesize);
	if (oob_required)
		fsl_elbc_read_buf(chip, chip->oob_poi, mtd->oobsize);

	if (fsl_elbc_wait(chip) & NAND_STATUS_FAIL)
		mtd->ecc_stats.failed++;

	return elbc_fcm_ctrl->max_bitflips;
}