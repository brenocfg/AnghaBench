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
struct sd_info {int sd_clock; int capacity; int /*<<< orphan*/  raw_csd; int /*<<< orphan*/  sd_addr; } ;
struct rtsx_chip {int /*<<< orphan*/  card_wp; scalar_t__ asic_code; struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MMC_SECTOR_MODE (struct sd_info*) ; 
 int /*<<< orphan*/  CHK_SD_HCXC (struct sd_info*) ; 
 void* CLK_20 ; 
 int CLK_30 ; 
 int CLK_40 ; 
 int CLK_50 ; 
 int /*<<< orphan*/  SD_CARD ; 
 int /*<<< orphan*/  SD_NO_CARD ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R2 ; 
 int /*<<< orphan*/  SEND_CSD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_check_csd(struct rtsx_chip *chip, char check_wp)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;
	int i;
	u8 csd_ver, trans_speed;
	u8 rsp[16];

	for (i = 0; i < 6; i++) {
		if (detect_card_cd(chip, SD_CARD) != STATUS_SUCCESS) {
			sd_set_err_code(chip, SD_NO_CARD);
			return STATUS_FAIL;
		}

		retval = sd_send_cmd_get_rsp(chip, SEND_CSD, sd_card->sd_addr,
					     SD_RSP_TYPE_R2, rsp, 16);
		if (retval == STATUS_SUCCESS)
			break;
	}

	if (i == 6)
		return STATUS_FAIL;

	memcpy(sd_card->raw_csd, rsp + 1, 15);

	dev_dbg(rtsx_dev(chip), "CSD Response:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 16, sd_card->raw_csd);

	csd_ver = (rsp[1] & 0xc0) >> 6;
	dev_dbg(rtsx_dev(chip), "csd_ver = %d\n", csd_ver);

	trans_speed = rsp[4];
	if ((trans_speed & 0x07) == 0x02) {
		if ((trans_speed & 0xf8) >= 0x30) {
			if (chip->asic_code)
				sd_card->sd_clock = 47;
			else
				sd_card->sd_clock = CLK_50;

		} else if ((trans_speed & 0xf8) == 0x28) {
			if (chip->asic_code)
				sd_card->sd_clock = 39;
			else
				sd_card->sd_clock = CLK_40;

		} else if ((trans_speed & 0xf8) == 0x20) {
			if (chip->asic_code)
				sd_card->sd_clock = 29;
			else
				sd_card->sd_clock = CLK_30;

		} else if ((trans_speed & 0xf8) >= 0x10) {
			if (chip->asic_code)
				sd_card->sd_clock = 23;
			else
				sd_card->sd_clock = CLK_20;

		} else if ((trans_speed & 0x08) >= 0x08) {
			if (chip->asic_code)
				sd_card->sd_clock = 19;
			else
				sd_card->sd_clock = CLK_20;
		} else {
			return STATUS_FAIL;
		}
	} else {
		return STATUS_FAIL;
	}

	if (CHK_MMC_SECTOR_MODE(sd_card)) {
		sd_card->capacity = 0;
	} else {
		if ((!CHK_SD_HCXC(sd_card)) || (csd_ver == 0)) {
			u8 blk_size, c_size_mult;
			u16 c_size;

			blk_size = rsp[6] & 0x0F;
			c_size =  ((u16)(rsp[7] & 0x03) << 10)
					+ ((u16)rsp[8] << 2)
					+ ((u16)(rsp[9] & 0xC0) >> 6);
			c_size_mult = (u8)((rsp[10] & 0x03) << 1);
			c_size_mult += (rsp[11] & 0x80) >> 7;
			sd_card->capacity = (((u32)(c_size + 1)) *
					(1 << (c_size_mult + 2)))
				<< (blk_size - 9);
		} else {
			u32 total_sector = 0;

			total_sector = (((u32)rsp[8] & 0x3f) << 16) |
				((u32)rsp[9] << 8) | (u32)rsp[10];
			sd_card->capacity = (total_sector + 1) << 10;
		}
	}

	if (check_wp) {
		if (rsp[15] & 0x30)
			chip->card_wp |= SD_CARD;

		dev_dbg(rtsx_dev(chip), "CSD WP Status: 0x%x\n", rsp[15]);
	}

	return STATUS_SUCCESS;
}