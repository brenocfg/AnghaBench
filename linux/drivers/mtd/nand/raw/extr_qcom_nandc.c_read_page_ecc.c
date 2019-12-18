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
typedef  int /*<<< orphan*/  u8 ;
struct nand_ecc_ctrl {int steps; int size; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct qcom_nand_host {int ecc_bytes_hw; int spare_bytes; int cw_data; int bbm_size; struct nand_chip chip; } ;
struct qcom_nand_controller {int /*<<< orphan*/  dev; TYPE_1__* props; } ;
struct TYPE_2__ {scalar_t__ is_bam; } ;

/* Variables and functions */
 scalar_t__ FLASH_BUF_ACC ; 
 int /*<<< orphan*/  config_nand_cw_read (struct qcom_nand_controller*,int) ; 
 int /*<<< orphan*/  config_nand_page_read (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_descs (struct qcom_nand_controller*) ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nandc_set_read_loc (struct qcom_nand_controller*,int,int,int,int) ; 
 int parse_read_errors (struct qcom_nand_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_data_dma (struct qcom_nand_controller*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int submit_descs (struct qcom_nand_controller*) ; 

__attribute__((used)) static int read_page_ecc(struct qcom_nand_host *host, u8 *data_buf,
			 u8 *oob_buf, int page)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *data_buf_start = data_buf, *oob_buf_start = oob_buf;
	int i, ret;

	config_nand_page_read(nandc);

	/* queue cmd descs for each codeword */
	for (i = 0; i < ecc->steps; i++) {
		int data_size, oob_size;

		if (i == (ecc->steps - 1)) {
			data_size = ecc->size - ((ecc->steps - 1) << 2);
			oob_size = (ecc->steps << 2) + host->ecc_bytes_hw +
				   host->spare_bytes;
		} else {
			data_size = host->cw_data;
			oob_size = host->ecc_bytes_hw + host->spare_bytes;
		}

		if (nandc->props->is_bam) {
			if (data_buf && oob_buf) {
				nandc_set_read_loc(nandc, 0, 0, data_size, 0);
				nandc_set_read_loc(nandc, 1, data_size,
						   oob_size, 1);
			} else if (data_buf) {
				nandc_set_read_loc(nandc, 0, 0, data_size, 1);
			} else {
				nandc_set_read_loc(nandc, 0, data_size,
						   oob_size, 1);
			}
		}

		config_nand_cw_read(nandc, true);

		if (data_buf)
			read_data_dma(nandc, FLASH_BUF_ACC, data_buf,
				      data_size, 0);

		/*
		 * when ecc is enabled, the controller doesn't read the real
		 * or dummy bad block markers in each chunk. To maintain a
		 * consistent layout across RAW and ECC reads, we just
		 * leave the real/dummy BBM offsets empty (i.e, filled with
		 * 0xffs)
		 */
		if (oob_buf) {
			int j;

			for (j = 0; j < host->bbm_size; j++)
				*oob_buf++ = 0xff;

			read_data_dma(nandc, FLASH_BUF_ACC + data_size,
				      oob_buf, oob_size, 0);
		}

		if (data_buf)
			data_buf += data_size;
		if (oob_buf)
			oob_buf += oob_size;
	}

	ret = submit_descs(nandc);
	free_descs(nandc);

	if (ret) {
		dev_err(nandc->dev, "failure to read page/oob\n");
		return ret;
	}

	return parse_read_errors(host, data_buf_start, oob_buf_start, page);
}