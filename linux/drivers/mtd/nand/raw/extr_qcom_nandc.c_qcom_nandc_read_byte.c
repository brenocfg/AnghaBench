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
typedef  int uint8_t ;
typedef  int u8 ;
struct qcom_nand_host {scalar_t__ last_command; int status; } ;
struct qcom_nand_controller {int* data_buffer; scalar_t__ buf_start; scalar_t__ buf_count; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NAND_CMD_STATUS ; 
 int NAND_STATUS_READY ; 
 int NAND_STATUS_WP ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 struct qcom_nand_host* to_qcom_nand_host (struct nand_chip*) ; 

__attribute__((used)) static uint8_t qcom_nandc_read_byte(struct nand_chip *chip)
{
	struct qcom_nand_host *host = to_qcom_nand_host(chip);
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	u8 *buf = nandc->data_buffer;
	u8 ret = 0x0;

	if (host->last_command == NAND_CMD_STATUS) {
		ret = host->status;

		host->status = NAND_STATUS_READY | NAND_STATUS_WP;

		return ret;
	}

	if (nandc->buf_start < nandc->buf_count)
		ret = buf[nandc->buf_start++];

	return ret;
}