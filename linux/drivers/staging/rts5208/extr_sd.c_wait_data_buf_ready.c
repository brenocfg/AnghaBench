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
struct sd_info {int /*<<< orphan*/  sd_addr; scalar_t__ sd_data_buf_ready; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CARD ; 
 int /*<<< orphan*/  SD_NO_CARD ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1 ; 
 int /*<<< orphan*/  SD_TO_ERR ; 
 int /*<<< orphan*/  SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int WAIT_DATA_READY_RTY_CNT ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_data_buf_ready(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int i, retval;

	for (i = 0; i < WAIT_DATA_READY_RTY_CNT; i++) {
		if (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) {
			sd_set_err_code(chip, SD_NO_CARD);
			return STATUS_FAIL;
		}

		sd_card->sd_data_buf_ready = 0;

		retval = sd_send_cmd_get_rsp(chip, SEND_STATUS,
					     sd_card->sd_addr, SD_RSP_TYPE_R1,
					     NULL, 0);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		if (sd_card->sd_data_buf_ready) {
			return sd_send_cmd_get_rsp(chip, SEND_STATUS,
				sd_card->sd_addr, SD_RSP_TYPE_R1, NULL, 0);
		}
	}

	sd_set_err_code(chip, SD_TO_ERR);

	return STATUS_FAIL;
}