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
struct qcom_nand_host {int use_ecc; int cw_size; } ;
struct qcom_nand_controller {int* data_buffer; int /*<<< orphan*/  dev; } ;
struct nand_ecc_ctrl {int steps; } ;
struct nand_chip {int page_shift; int pagemask; int options; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int writesize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ check_flash_errors (struct qcom_nand_host*,int) ; 
 int /*<<< orphan*/  clear_bam_transaction (struct qcom_nand_controller*) ; 
 int copy_last_cw (struct qcom_nand_host*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 

__attribute__((used)) static int qcom_nandc_block_bad(struct nand_chip *chip, loff_t ofs)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int page, ret, bbpos, bad = 0;

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	/*
	 * configure registers for a raw sub page read, the address is set to
	 * the beginning of the last codeword, we don't care about reading ecc
	 * portion of oob. we just want the first few bytes from this codeword
	 * that contains the BBM
	 */
	host->use_ecc = false;

	clear_bam_transaction(nandc);
	ret = copy_last_cw(host, page);
	if (ret)
		goto err;

	if (check_flash_errors(host, 1)) {
		dev_warn(nandc->dev, "error when trying to read BBM\n");
		goto err;
	}

	bbpos = mtd->writesize - host->cw_size * (ecc->steps - 1);

	bad = nandc->data_buffer[bbpos] != 0xff;

	if (chip->options & NAND_BUSWIDTH_16)
		bad = bad || (nandc->data_buffer[bbpos + 1] != 0xff);
err:
	return bad;
}