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
struct ms_info {int boot_block; int block_shift; int page_off; int total_block; int capacity; int /*<<< orphan*/  ms_type; int /*<<< orphan*/  raw_sys_info; } ;
struct rtsx_chip {size_t card_wp; int* capacity; size_t* card2lun; int* card_bus_width; struct ms_info ms_card; } ;

/* Variables and functions */
 int BLOCK_OK ; 
 int BLOCK_SIZE_0 ; 
 scalar_t__ CHK_MS4BIT (struct ms_info*) ; 
 int DISABLED_BLOCK0 ; 
 int DISABLED_BLOCK3 ; 
 int HEADER_ID0 ; 
 int HEADER_ID1 ; 
 int MAX_DEFECTIVE_BLOCK ; 
 int /*<<< orphan*/  MS_4BIT ; 
 int MS_4bit_Support ; 
 int MS_BUS_WIDTH_4 ; 
 size_t MS_CARD ; 
 int MS_CFG ; 
 int MS_Device_Type ; 
 int MS_EXTRA_SIZE ; 
 int /*<<< orphan*/  MS_FLASH_WRITE_ERROR ; 
 int /*<<< orphan*/  MS_NO_CARD ; 
 int MS_NO_CHECK_INT ; 
 int /*<<< orphan*/  MS_NO_ERROR ; 
 int /*<<< orphan*/  MS_RESET ; 
 int /*<<< orphan*/  MS_TM_WRITE_BYTES ; 
 int NOT_BOOT_BLOCK ; 
 int /*<<< orphan*/  NO_WAIT_INT ; 
 int PAGE_SIZE_1 ; 
 int PPBUF_BASE2 ; 
 int PUSH_TIME_ODD ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemParm ; 
 int /*<<< orphan*/  TYPE_MS ; 
 int /*<<< orphan*/  WRITE_REG ; 
 int WRT_PRTCT ; 
 int detect_card_cd (struct rtsx_chip*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ ms_check_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int ms_prepare_reset (struct rtsx_chip*) ; 
 int ms_read_extra_data (struct rtsx_chip*,int,int /*<<< orphan*/ ,int*,int) ; 
 int ms_read_page (struct rtsx_chip*,int,int) ; 
 int ms_read_status_reg (struct rtsx_chip*) ; 
 int ms_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int ms_set_rw_reg_addr (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ms_transfer_tpc (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int,int*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,size_t,int) ; 
 int rtsx_write_register (struct rtsx_chip*,int,int,int) ; 

__attribute__((used)) static int reset_ms(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;
	u16 i, reg_addr, block_size;
	u8 val, extra[MS_EXTRA_SIZE], j, *ptr;
#ifndef SUPPORT_MAGIC_GATE
	u16 eblock_cnt;
#endif

	retval = ms_prepare_reset(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	ms_card->ms_type |= TYPE_MS;

	retval = ms_send_cmd(chip, MS_RESET, NO_WAIT_INT);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = ms_read_status_reg(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_read_register(chip, PPBUF_BASE2, &val);
	if (retval)
		return retval;

	if (val & WRT_PRTCT)
		chip->card_wp |= MS_CARD;
	else
		chip->card_wp &= ~MS_CARD;

	i = 0;

RE_SEARCH:
	/* Search Boot Block */
	while (i < (MAX_DEFECTIVE_BLOCK + 2)) {
		if (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) {
			ms_set_err_code(chip, MS_NO_CARD);
			return STATUS_FAIL;
		}

		retval = ms_read_extra_data(chip, i, 0, extra, MS_EXTRA_SIZE);
		if (retval != STATUS_SUCCESS) {
			i++;
			continue;
		}

		if (extra[0] & BLOCK_OK) {
			if (!(extra[1] & NOT_BOOT_BLOCK)) {
				ms_card->boot_block = i;
				break;
			}
		}
		i++;
	}

	if (i == (MAX_DEFECTIVE_BLOCK + 2)) {
		dev_dbg(rtsx_dev(chip), "No boot block found!");
		return STATUS_FAIL;
	}

	for (j = 0; j < 3; j++) {
		retval = ms_read_page(chip, ms_card->boot_block, j);
		if (retval != STATUS_SUCCESS) {
			if (ms_check_err_code(chip, MS_FLASH_WRITE_ERROR)) {
				i = ms_card->boot_block + 1;
				ms_set_err_code(chip, MS_NO_ERROR);
				goto RE_SEARCH;
			}
		}
	}

	retval = ms_read_page(chip, ms_card->boot_block, 0);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	/* Read MS system information as sys_info */
	rtsx_init_cmd(chip);

	for (i = 0; i < 96; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + 0x1A0 + i, 0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	if (retval < 0)
		return STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip);
	memcpy(ms_card->raw_sys_info, ptr, 96);

	/* Read useful block contents */
	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, READ_REG_CMD, HEADER_ID0, 0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, HEADER_ID1, 0, 0);

	for (reg_addr = DISABLED_BLOCK0; reg_addr <= DISABLED_BLOCK3;
	     reg_addr++)
		rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

	for (reg_addr = BLOCK_SIZE_0; reg_addr <= PAGE_SIZE_1; reg_addr++)
		rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

	rtsx_add_cmd(chip, READ_REG_CMD, MS_Device_Type, 0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, MS_4bit_Support, 0, 0);

	retval = rtsx_send_cmd(chip, MS_CARD, 100);
	if (retval < 0)
		return STATUS_FAIL;

	ptr = rtsx_get_cmd_data(chip);

	dev_dbg(rtsx_dev(chip), "Boot block data:\n");
	dev_dbg(rtsx_dev(chip), "%*ph\n", 16, ptr);

	/* Block ID error
	 * HEADER_ID0, HEADER_ID1
	 */
	if (ptr[0] != 0x00 || ptr[1] != 0x01) {
		i = ms_card->boot_block + 1;
		goto RE_SEARCH;
	}

	/* Page size error
	 * PAGE_SIZE_0, PAGE_SIZE_1
	 */
	if (ptr[12] != 0x02 || ptr[13] != 0x00) {
		i = ms_card->boot_block + 1;
		goto RE_SEARCH;
	}

	if ((ptr[14] == 1) || (ptr[14] == 3))
		chip->card_wp |= MS_CARD;

	/* BLOCK_SIZE_0, BLOCK_SIZE_1 */
	block_size = ((u16)ptr[6] << 8) | ptr[7];
	if (block_size == 0x0010) {
		/* Block size 16KB */
		ms_card->block_shift = 5;
		ms_card->page_off = 0x1F;
	} else if (block_size == 0x0008) {
		/* Block size 8KB */
		ms_card->block_shift = 4;
		ms_card->page_off = 0x0F;
	}

	/* BLOCK_COUNT_0, BLOCK_COUNT_1 */
	ms_card->total_block = ((u16)ptr[8] << 8) | ptr[9];

#ifdef SUPPORT_MAGIC_GATE
	j = ptr[10];

	if (ms_card->block_shift == 4)  { /* 4MB or 8MB */
		if (j < 2)  { /* Effective block for 4MB: 0x1F0 */
			ms_card->capacity = 0x1EE0;
		} else { /* Effective block for 8MB: 0x3E0 */
			ms_card->capacity = 0x3DE0;
		}
	} else  { /* 16MB, 32MB, 64MB or 128MB */
		if (j < 5)  { /* Effective block for 16MB: 0x3E0 */
			ms_card->capacity = 0x7BC0;
		} else if (j < 0xA) { /* Effective block for 32MB: 0x7C0 */
			ms_card->capacity = 0xF7C0;
		} else if (j < 0x11) { /* Effective block for 64MB: 0xF80 */
			ms_card->capacity = 0x1EF80;
		} else { /* Effective block for 128MB: 0x1F00 */
			ms_card->capacity = 0x3DF00;
		}
	}
#else
	/* EBLOCK_COUNT_0, EBLOCK_COUNT_1 */
	eblock_cnt = ((u16)ptr[10] << 8) | ptr[11];

	ms_card->capacity = ((u32)eblock_cnt - 2) << ms_card->block_shift;
#endif

	chip->capacity[chip->card2lun[MS_CARD]] = ms_card->capacity;

	/* Switch I/F Mode */
	if (ptr[15]) {
		retval = ms_set_rw_reg_addr(chip, 0, 0, SystemParm, 1);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		retval = rtsx_write_register(chip, PPBUF_BASE2, 0xFF, 0x88);
		if (retval)
			return retval;

		retval = rtsx_write_register(chip, PPBUF_BASE2 + 1, 0xFF, 0);
		if (retval)
			return retval;

		retval = ms_transfer_tpc(chip, MS_TM_WRITE_BYTES, WRITE_REG, 1,
					 NO_WAIT_INT);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		retval = rtsx_write_register(chip, MS_CFG,
					     0x58 | MS_NO_CHECK_INT,
					     MS_BUS_WIDTH_4 |
					     PUSH_TIME_ODD |
					     MS_NO_CHECK_INT);
		if (retval)
			return retval;

		ms_card->ms_type |= MS_4BIT;
	}

	if (CHK_MS4BIT(ms_card))
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 4;
	else
		chip->card_bus_width[chip->card2lun[MS_CARD]] = 1;

	return STATUS_SUCCESS;
}