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
typedef  int u32 ;
typedef  int u16 ;
struct xd_info {int device_code; int block_shift; int page_off; int addr_cycle; int zone_cnt; int capacity; int cis_block; } ;
struct rtsx_chip {int ocp_stat; int* capacity; size_t* card2lun; scalar_t__ ft2_fast_mode; scalar_t__ asic_code; struct xd_info xd_card; } ;

/* Variables and functions */
 size_t BLOCK_STATUS ; 
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  CHECK_PID (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  FPGA_PULL_CTL ; 
 int FPGA_XD_PULL_CTL_EN1 ; 
 int FPGA_XD_PULL_CTL_EN2 ; 
 int FPGA_XD_PULL_CTL_EN3 ; 
 size_t PAGE_STATUS ; 
 size_t PARITY ; 
 int READY_FLAG ; 
 int READY_STATE ; 
 int /*<<< orphan*/  READ_ID ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int /*<<< orphan*/  READ_xD_ID ; 
 int SD_OC_EVER ; 
 int SD_OC_NOW ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
#define  XD_128M_X8_512 138 
#define  XD_16M_X8_512 137 
#define  XD_256M_X8_512 136 
#define  XD_32M_X8_512 135 
#define  XD_4M_X8_512_1 134 
#define  XD_4M_X8_512_2 133 
#define  XD_512M_X8 132 
#define  XD_64M_X8_512 131 
#define  XD_8M_X8_512 130 
 int XD_BA1_ALL0 ; 
 size_t XD_CARD ; 
 int /*<<< orphan*/  XD_CATCTL ; 
 int XD_CE_DISEN ; 
 int /*<<< orphan*/  XD_CHK_DATA_STATUS ; 
 int /*<<< orphan*/  XD_CTL ; 
 int /*<<< orphan*/  XD_DAT ; 
 int /*<<< orphan*/  XD_DTCTL ; 
 int XD_GBLK ; 
 int XD_GPG ; 
 int XD_ID_CODE ; 
 int /*<<< orphan*/  XD_INIT ; 
 int XD_NO_AUTO_PWR_OFF ; 
 int XD_OUTPUT_EN ; 
 int /*<<< orphan*/  XD_PAGE_512 (struct xd_info*) ; 
 int XD_PGSTS_NOT_FF ; 
 int XD_RDY ; 
 int XD_RESET ; 
 int /*<<< orphan*/  XD_SET_4MB (struct xd_info*) ; 
 int XD_TIME_RWN_STEP ; 
 int XD_TIME_RW_STEP ; 
 int XD_TIME_SETUP_STEP ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int card_power_off (struct rtsx_chip*,size_t) ; 
 int card_power_on (struct rtsx_chip*,size_t) ; 
 int detect_card_cd (struct rtsx_chip*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,size_t,int) ; 
 int select_card (struct rtsx_chip*,size_t) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 
#define  xD_1G_X8_512 129 
#define  xD_2G_X8_512 128 
 int /*<<< orphan*/  xd_fill_pull_ctl_disable (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_fill_pull_ctl_enable (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_fill_pull_ctl_stage1_barossa (struct rtsx_chip*) ; 
 int xd_read_cis (struct rtsx_chip*,int,int*,int) ; 
 int xd_read_id (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int) ; 
 int xd_read_redundant (struct rtsx_chip*,int,int*,int) ; 
 int xd_set_init_para (struct rtsx_chip*) ; 

__attribute__((used)) static int reset_xd(struct rtsx_chip *chip)
{
	struct xd_info *xd_card = &chip->xd_card;
	int retval, i, j;
	u8 *ptr, id_buf[4], redunt[11];

	retval = select_card(chip, XD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS, 0xFF,
		     XD_PGSTS_NOT_FF);
	if (chip->asic_code) {
		if (!CHECK_PID(chip, 0x5288))
			xd_fill_pull_ctl_disable(chip);
		else
			xd_fill_pull_ctl_stage1_barossa(chip);
	} else {
		rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
			     (FPGA_XD_PULL_CTL_EN1 & FPGA_XD_PULL_CTL_EN3) |
			     0x20);
	}

	if (!chip->ft2_fast_mode)
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_INIT,
			     XD_NO_AUTO_PWR_OFF, 0);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_OE, XD_OUTPUT_EN, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 100);
	if (retval < 0)
		return STATUS_FAIL;

	if (!chip->ft2_fast_mode) {
		retval = card_power_off(chip, XD_CARD);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		wait_timeout(250);

		rtsx_init_cmd(chip);

		if (chip->asic_code) {
			xd_fill_pull_ctl_enable(chip);
		} else {
			rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
				     (FPGA_XD_PULL_CTL_EN1 &
				      FPGA_XD_PULL_CTL_EN2) |
				     0x20);
		}

		retval = rtsx_send_cmd(chip, XD_CARD, 100);
		if (retval < 0)
			return STATUS_FAIL;

		retval = card_power_on(chip, XD_CARD);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

#ifdef SUPPORT_OCP
		wait_timeout(50);
		if (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) {
			dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			return STATUS_FAIL;
		}
#endif
	}

	rtsx_init_cmd(chip);

	if (chip->ft2_fast_mode) {
		if (chip->asic_code) {
			xd_fill_pull_ctl_enable(chip);
		} else {
			rtsx_add_cmd(chip, WRITE_REG_CMD, FPGA_PULL_CTL, 0xFF,
				     (FPGA_XD_PULL_CTL_EN1 &
				      FPGA_XD_PULL_CTL_EN2) |
				     0x20);
		}
	}

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_OE, XD_OUTPUT_EN, XD_OUTPUT_EN);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CTL, XD_CE_DISEN, XD_CE_DISEN);

	retval = rtsx_send_cmd(chip, XD_CARD, 100);
	if (retval < 0)
		return STATUS_FAIL;

	if (!chip->ft2_fast_mode)
		wait_timeout(200);

	retval = xd_set_init_para(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	/* Read ID to check if the timing setting is right */
	for (i = 0; i < 4; i++) {
		rtsx_init_cmd(chip);

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_DTCTL, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_RW_STEP * (2 + i) + XD_TIME_RWN_STEP * i);
		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CATCTL, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_RW_STEP * (4 + i) +
			     XD_TIME_RWN_STEP * (3 + i));

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_RESET);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);

		rtsx_add_cmd(chip, READ_REG_CMD, XD_DAT, 0, 0);
		rtsx_add_cmd(chip, READ_REG_CMD, XD_CTL, 0, 0);

		retval = rtsx_send_cmd(chip, XD_CARD, 100);
		if (retval < 0)
			return STATUS_FAIL;

		ptr = rtsx_get_cmd_data(chip) + 1;

		dev_dbg(rtsx_dev(chip), "XD_DAT: 0x%x, XD_CTL: 0x%x\n",
			ptr[0], ptr[1]);

		if (((ptr[0] & READY_FLAG) != READY_STATE) ||
		    !(ptr[1] & XD_RDY))
			continue;

		retval = xd_read_id(chip, READ_ID, id_buf, 4);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		dev_dbg(rtsx_dev(chip), "READ_ID: 0x%x 0x%x 0x%x 0x%x\n",
			id_buf[0], id_buf[1], id_buf[2], id_buf[3]);

		xd_card->device_code = id_buf[1];

		/* Check if the xD card is supported */
		switch (xd_card->device_code) {
		case XD_4M_X8_512_1:
		case XD_4M_X8_512_2:
			xd_card->block_shift = 4;
			xd_card->page_off = 0x0F;
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 8000;
			XD_SET_4MB(xd_card);
			break;
		case XD_8M_X8_512:
			xd_card->block_shift = 4;
			xd_card->page_off = 0x0F;
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 16000;
			break;
		case XD_16M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 1;
			xd_card->capacity = 32000;
			break;
		case XD_32M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 3;
			xd_card->zone_cnt = 2;
			xd_card->capacity = 64000;
			break;
		case XD_64M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 4;
			xd_card->capacity = 128000;
			break;
		case XD_128M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 8;
			xd_card->capacity = 256000;
			break;
		case XD_256M_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 16;
			xd_card->capacity = 512000;
			break;
		case XD_512M_X8:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 32;
			xd_card->capacity = 1024000;
			break;
		case xD_1G_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 64;
			xd_card->capacity = 2048000;
			break;
		case xD_2G_X8_512:
			XD_PAGE_512(xd_card);
			xd_card->addr_cycle = 4;
			xd_card->zone_cnt = 128;
			xd_card->capacity = 4096000;
			break;
		default:
			continue;
		}

		/* Confirm timing setting */
		for (j = 0; j < 10; j++) {
			retval = xd_read_id(chip, READ_ID, id_buf, 4);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;

			if (id_buf[1] != xd_card->device_code)
				break;
		}

		if (j == 10)
			break;
	}

	if (i == 4) {
		xd_card->block_shift = 0;
		xd_card->page_off = 0;
		xd_card->addr_cycle = 0;
		xd_card->capacity = 0;

		return STATUS_FAIL;
	}

	retval = xd_read_id(chip, READ_xD_ID, id_buf, 4);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;
	dev_dbg(rtsx_dev(chip), "READ_xD_ID: 0x%x 0x%x 0x%x 0x%x\n",
		id_buf[0], id_buf[1], id_buf[2], id_buf[3]);
	if (id_buf[2] != XD_ID_CODE)
		return STATUS_FAIL;

	/* Search CIS block */
	for (i = 0; i < 24; i++) {
		u32 page_addr;

		if (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS)
			return STATUS_FAIL;

		page_addr = (u32)i << xd_card->block_shift;

		for (j = 0; j < 3; j++) {
			retval = xd_read_redundant(chip, page_addr, redunt, 11);
			if (retval == STATUS_SUCCESS)
				break;
		}
		if (j == 3)
			continue;

		if (redunt[BLOCK_STATUS] != XD_GBLK)
			continue;

		j = 0;
		if (redunt[PAGE_STATUS] != XD_GPG) {
			for (j = 1; j <= 8; j++) {
				retval = xd_read_redundant(chip, page_addr + j,
							   redunt, 11);
				if (retval == STATUS_SUCCESS) {
					if (redunt[PAGE_STATUS] == XD_GPG)
						break;
				}
			}

			if (j == 9)
				break;
		}

		/* Check CIS data */
		if ((redunt[BLOCK_STATUS] == XD_GBLK) &&
		    (redunt[PARITY] & XD_BA1_ALL0)) {
			u8 buf[10];

			page_addr += j;

			retval = xd_read_cis(chip, page_addr, buf, 10);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;

			if ((buf[0] == 0x01) && (buf[1] == 0x03) &&
			    (buf[2] == 0xD9) &&
			    (buf[3] == 0x01) && (buf[4] == 0xFF) &&
			    (buf[5] == 0x18) && (buf[6] == 0x02) &&
			    (buf[7] == 0xDF) && (buf[8] == 0x01) &&
			    (buf[9] == 0x20)) {
				xd_card->cis_block = (u16)i;
			}
		}

		break;
	}

	dev_dbg(rtsx_dev(chip), "CIS block: 0x%x\n", xd_card->cis_block);
	if (xd_card->cis_block == 0xFFFF)
		return STATUS_FAIL;

	chip->capacity[chip->card2lun[XD_CARD]] = xd_card->capacity;

	return STATUS_SUCCESS;
}