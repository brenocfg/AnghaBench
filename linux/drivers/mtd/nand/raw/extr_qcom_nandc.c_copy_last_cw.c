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
struct nand_ecc_ctrl {int steps; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct qcom_nand_host {int cw_data; int cw_size; scalar_t__ use_ecc; struct nand_chip chip; } ;
struct qcom_nand_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  data_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_BUF_ACC ; 
 int /*<<< orphan*/  clear_read_regs (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  config_nand_single_cw_page_read (struct qcom_nand_controller*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  read_data_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_address (struct qcom_nand_host*,int,int) ; 
 int submit_descs (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int,int) ; 

__attribute__((used)) static int copy_last_cw(struct qcom_nand_host *host, int page)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int size;
	int ret;

	clear_read_regs(nandc);

	size = host->use_ecc ? host->cw_data : host->cw_size;

	/* prepare a clean read buffer */
	memset(nandc->data_buffer, 0xff, size);

	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, true);

	config_nand_single_cw_page_read(nandc, host->use_ecc);

	read_data_dma(nandc, FLASH_BUF_ACC, nandc->data_buffer, size, 0);

	ret = submit_descs(nandc);
	if (ret)
		dev_err(nandc->dev, "failed to copy last codeword\n");

	free_descs(nandc);

	return ret;
}