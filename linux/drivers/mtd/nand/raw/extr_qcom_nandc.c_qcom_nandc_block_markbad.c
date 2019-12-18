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
struct qcom_nand_host {int cw_size; int use_ecc; } ;
struct qcom_nand_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  data_buffer; } ;
struct nand_ecc_ctrl {int steps; } ;
struct nand_chip {int page_shift; int pagemask; struct nand_ecc_ctrl ecc; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FLASH_BUF_ACC ; 
 int /*<<< orphan*/  clear_bam_transaction (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  clear_read_regs (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_cw_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_page_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  set_address (struct qcom_nand_host*,int,int) ; 
 int submit_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int,int) ; 
 int /*<<< orphan*/  write_data_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_nandc_block_markbad(struct nand_chip *chip, loff_t ofs)
{
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int page, ret;

	clear_read_regs(nandc);
	clear_bam_transaction(nandc);

	/*
	 * to mark the BBM as bad, we flash the entire last codeword with 0s.
	 * we don't care about the rest of the content in the codeword since
	 * we aren't going to use this block again
	 */
	memset(nandc->data_buffer, 0x00, host->cw_size);

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	/* prepare write */
	host->use_ecc = false;
	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, false);

	config_nand_page_write(nandc);
	write_data_dma(nandc, FLASH_BUF_ACC,
		       nandc->data_buffer, host->cw_size, 0);
	config_nand_cw_write(nandc);

	ret = submit_descs(nandc);

	free_descs(nandc);

	if (ret) {
		dev_err(nandc->dev, "failure to update BBM\n");
		return -EIO;
	}

	return nand_prog_page_end_op(chip);
}