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
struct qcom_nand_host {int use_ecc; } ;
struct qcom_nand_controller {int buf_count; int /*<<< orphan*/  dev; } ;
struct nand_ecc_ctrl {int /*<<< orphan*/  steps; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;

/* Variables and functions */
#define  NAND_CMD_ERASE1 136 
#define  NAND_CMD_NONE 135 
#define  NAND_CMD_PAGEPROG 134 
#define  NAND_CMD_PARAM 133 
#define  NAND_CMD_READ0 132 
#define  NAND_CMD_READID 131 
#define  NAND_CMD_RESET 130 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int erase_block (struct qcom_nand_host*,int) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int nandc_param (struct qcom_nand_host*) ; 
 int /*<<< orphan*/  post_command (struct qcom_nand_host*,unsigned int) ; 
 int /*<<< orphan*/  pre_command (struct qcom_nand_host*,unsigned int) ; 
 int read_id (struct qcom_nand_host*,int) ; 
 int reset (struct qcom_nand_host*) ; 
 int /*<<< orphan*/  set_address (struct qcom_nand_host*,int /*<<< orphan*/ ,int) ; 
 int submit_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qcom_nandc_command(struct nand_chip *chip, unsigned int command,
			       int column, int page_addr)
{
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	bool wait = false;
	int ret = 0;

	pre_command(host, command);

	switch (command) {
	case NAND_CMD_RESET:
		ret = reset(host);
		wait = true;
		break;

	case NAND_CMD_READID:
		nandc->buf_count = 4;
		ret = read_id(host, column);
		wait = true;
		break;

	case NAND_CMD_PARAM:
		ret = nandc_param(host);
		wait = true;
		break;

	case NAND_CMD_ERASE1:
		ret = erase_block(host, page_addr);
		wait = true;
		break;

	case NAND_CMD_READ0:
		/* we read the entire page for now */
		WARN_ON(column != 0);

		host->use_ecc = true;
		set_address(host, 0, page_addr);
		update_rw_regs(host, ecc->steps, true);
		break;

	case NAND_CMD_SEQIN:
		WARN_ON(column != 0);
		set_address(host, 0, page_addr);
		break;

	case NAND_CMD_PAGEPROG:
	case NAND_CMD_STATUS:
	case NAND_CMD_NONE:
	default:
		break;
	}

	if (ret) {
		dev_err(nandc->dev, "failure executing command %d\n",
			command);
		free_descs(nandc);
		return;
	}

	if (wait) {
		ret = submit_descs(nandc);
		if (ret)
			dev_err(nandc->dev,
				"failure submitting descs for command %d\n",
				command);
	}

	free_descs(nandc);

	post_command(host, command);
}