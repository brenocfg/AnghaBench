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
struct qcom_nand_host {int use_ecc; int cw_size; int /*<<< orphan*/  cw_data; } ;
struct qcom_nand_controller {int /*<<< orphan*/  dev; scalar_t__ data_buffer; } ;
struct nand_ecc_ctrl {int size; int steps; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int oobavail; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FLASH_BUF_ACC ; 
 int /*<<< orphan*/  clear_bam_transaction (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_cw_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_page_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_ooblayout_get_databytes (struct mtd_info*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  set_address (struct qcom_nand_host*,int,int) ; 
 int submit_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int,int) ; 
 int /*<<< orphan*/  write_data_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_nandc_write_oob(struct nand_chip *chip, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *oob = chip->oob_poi;
	int data_size, oob_size;
	int ret;

	host->use_ecc = true;
	clear_bam_transaction(nandc);

	/* calculate the data and oob size for the last codeword/step */
	data_size = ecc->size - ((ecc->steps - 1) << 2);
	oob_size = mtd->oobavail;

	memset(nandc->data_buffer, 0xff, host->cw_data);
	/* override new oob content to last codeword */
	mtd_ooblayout_get_databytes(mtd, nandc->data_buffer + data_size, oob,
				    0, mtd->oobavail);

	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, false);

	config_nand_page_write(nandc);
	write_data_dma(nandc, FLASH_BUF_ACC,
		       nandc->data_buffer, data_size + oob_size, 0);
	config_nand_cw_write(nandc);

	ret = submit_descs(nandc);

	free_descs(nandc);

	if (ret) {
		dev_err(nandc->dev, "failure to write oob\n");
		return -EIO;
	}

	return nand_prog_page_end_op(chip);
}