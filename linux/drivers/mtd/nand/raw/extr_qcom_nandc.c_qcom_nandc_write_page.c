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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct qcom_nand_host {int use_ecc; int ecc_bytes_hw; int spare_bytes; int cw_data; int /*<<< orphan*/  bbm_size; } ;
struct qcom_nand_controller {int /*<<< orphan*/  dev; } ;
struct nand_ecc_ctrl {int steps; int size; int bytes; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; struct nand_ecc_ctrl ecc; } ;

/* Variables and functions */
 scalar_t__ FLASH_BUF_ACC ; 
 int /*<<< orphan*/  NAND_BAM_NO_EOT ; 
 int /*<<< orphan*/  clear_bam_transaction (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  clear_read_regs (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_cw_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_page_write (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int submit_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int,int) ; 
 int /*<<< orphan*/  write_data_dma (struct qcom_nand_controller*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_nandc_write_page(struct nand_chip *chip, const uint8_t *buf,
				 int oob_required, int page)
{
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *data_buf, *oob_buf;
	int i, ret;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	clear_read_regs(nandc);
	clear_bam_transaction(nandc);

	data_buf = (u8 *)buf;
	oob_buf = chip->oob_poi;

	host->use_ecc = true;
	update_rw_regs(host, ecc->steps, false);
	config_nand_page_write(nandc);

	for (i = 0; i < ecc->steps; i++) {
		int data_size, oob_size;

		if (i == (ecc->steps - 1)) {
			data_size = ecc->size - ((ecc->steps - 1) << 2);
			oob_size = (ecc->steps << 2) + host->ecc_bytes_hw +
				   host->spare_bytes;
		} else {
			data_size = host->cw_data;
			oob_size = ecc->bytes;
		}


		write_data_dma(nandc, FLASH_BUF_ACC, data_buf, data_size,
			       i == (ecc->steps - 1) ? NAND_BAM_NO_EOT : 0);

		/*
		 * when ECC is enabled, we don't really need to write anything
		 * to oob for the first n - 1 codewords since these oob regions
		 * just contain ECC bytes that's written by the controller
		 * itself. For the last codeword, we skip the bbm positions and
		 * write to the free oob area.
		 */
		if (i == (ecc->steps - 1)) {
			oob_buf += host->bbm_size;

			write_data_dma(nandc, FLASH_BUF_ACC + data_size,
				       oob_buf, oob_size, 0);
		}

		config_nand_cw_write(nandc);

		data_buf += data_size;
		oob_buf += oob_size;
	}

	ret = submit_descs(nandc);
	if (ret)
		dev_err(nandc->dev, "failure to write page\n");

	free_descs(nandc);

	if (!ret)
		ret = nand_prog_page_end_op(chip);

	return ret;
}