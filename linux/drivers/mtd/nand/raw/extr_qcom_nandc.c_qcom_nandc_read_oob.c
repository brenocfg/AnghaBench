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
struct qcom_nand_controller {int dummy; } ;
struct nand_ecc_ctrl {int /*<<< orphan*/  steps; } ;
struct nand_chip {int /*<<< orphan*/  oob_poi; struct nand_ecc_ctrl ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bam_transaction (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  clear_read_regs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int read_page_ecc (struct qcom_nand_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_address (struct qcom_nand_host*,int /*<<< orphan*/ ,int) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 
 int /*<<< orphan*/  update_rw_regs (struct qcom_nand_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qcom_nandc_read_oob(struct nand_chip *chip, int page)
{
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	clear_read_regs(nandc);
	clear_bam_transaction(nandc);

	host->use_ecc = true;
	set_address(host, 0, page);
	update_rw_regs(host, ecc->steps, true);

	return read_page_ecc(host, NULL, chip->oob_poi, page);
}