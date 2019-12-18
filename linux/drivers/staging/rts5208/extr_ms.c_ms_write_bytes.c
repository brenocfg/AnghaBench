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
typedef  int u8 ;
struct ms_info {int dummy; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 scalar_t__ MS_BYTE_CNT ; 
 int /*<<< orphan*/  MS_CARD ; 
 int /*<<< orphan*/  MS_CMD_NK ; 
 int MS_CRC16_ERR ; 
 int /*<<< orphan*/  MS_CRC16_ERROR ; 
 int MS_INT_CMDNK ; 
 int MS_INT_ERR ; 
 int MS_RDY_TIMEOUT ; 
 int MS_TM_WRITE_BYTES ; 
 int /*<<< orphan*/  MS_TO_ERROR ; 
 scalar_t__ MS_TPC ; 
 scalar_t__ MS_TRANSFER ; 
 int MS_TRANSFER_END ; 
 int MS_TRANSFER_START ; 
 scalar_t__ MS_TRANS_CFG ; 
 int PINGPONG_BUFFER ; 
 scalar_t__ PPBUF_BASE2 ; 
 int STATUS_ERROR ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ms_parse_err_code (struct rtsx_chip*) ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_ms_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_register (struct rtsx_chip*,scalar_t__,int*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ms_write_bytes(struct rtsx_chip *chip,
			  u8 tpc, u8 cnt, u8 cfg, u8 *data, int data_len)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval, i;

	if (!data || (data_len < cnt))
		return STATUS_ERROR;

	rtsx_init_cmd(chip);

	for (i = 0; i < cnt; i++) {
		rtsx_add_cmd(chip, WRITE_REG_CMD,
			     PPBUF_BASE2 + i, 0xFF, data[i]);
	}
	if (cnt % 2)
		rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2 + i, 0xFF, 0xFF);

	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TPC, 0xFF, tpc);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_BYTE_CNT, 0xFF, cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, MS_TRANS_CFG, 0xFF, cfg);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD,
		     MS_TRANSFER, 0xFF, MS_TRANSFER_START | MS_TM_WRITE_BYTES);
	rtsx_add_cmd(chip, CHECK_REG_CMD,
		     MS_TRANSFER, MS_TRANSFER_END, MS_TRANSFER_END);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	if (retval < 0) {
		u8 val = 0;

		rtsx_read_register(chip, MS_TRANS_CFG, &val);
		dev_dbg(rtsx_dev(chip), "MS_TRANS_CFG: 0x%02x\n", val);

		rtsx_clear_ms_error(chip);

		if (!(tpc & 0x08)) {
			if (val & MS_CRC16_ERR) {
				ms_set_err_code(chip, MS_CRC16_ERROR);
				return ms_parse_err_code(chip);
			}
		} else {
			if (CHK_MSPRO(ms_card) && !(val & 0x80)) {
				if (val & (MS_INT_ERR | MS_INT_CMDNK)) {
					ms_set_err_code(chip, MS_CMD_NK);
					return ms_parse_err_code(chip);
				}
			}
		}

		if (val & MS_RDY_TIMEOUT) {
			ms_set_err_code(chip, MS_TO_ERROR);
			return ms_parse_err_code(chip);
		}

		ms_set_err_code(chip, MS_TO_ERROR);
		return ms_parse_err_code(chip);
	}

	return STATUS_SUCCESS;
}