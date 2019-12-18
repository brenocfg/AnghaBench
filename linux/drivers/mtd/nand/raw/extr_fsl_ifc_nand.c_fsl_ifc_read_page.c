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
struct fsl_ifc_nand_ctrl {int max_bitflips; } ;
struct fsl_ifc_mtd {struct fsl_ifc_ctrl* ctrl; } ;
struct fsl_ifc_ctrl {int nand_stat; } ;

/* Variables and functions */
 int IFC_NAND_EVTER_STAT_ECCER ; 
 int IFC_NAND_EVTER_STAT_OPC ; 
 int check_erased_page (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_ifc_read_buf (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_ifc_nand_ctrl* ifc_nand_ctrl ; 
 struct fsl_ifc_mtd* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int fsl_ifc_read_page(struct nand_chip *chip, uint8_t *buf,
			     int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_nand_ctrl *nctrl = ifc_nand_ctrl;

	nand_read_page_op(chip, page, 0, buf, mtd->writesize);
	if (oob_required)
		fsl_ifc_read_buf(chip, chip->oob_poi, mtd->oobsize);

	if (ctrl->nand_stat & IFC_NAND_EVTER_STAT_ECCER) {
		if (!oob_required)
			fsl_ifc_read_buf(chip, chip->oob_poi, mtd->oobsize);

		return check_erased_page(chip, buf);
	}

	if (ctrl->nand_stat != IFC_NAND_EVTER_STAT_OPC)
		mtd->ecc_stats.failed++;

	return nctrl->max_bitflips;
}