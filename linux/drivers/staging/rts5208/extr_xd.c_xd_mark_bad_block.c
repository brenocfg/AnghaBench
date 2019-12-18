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
struct xd_info {int block_shift; int page_off; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int BLK_NOT_FOUND ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int PROGRAM_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  XD_BLOCK_ADDR1_H ; 
 int /*<<< orphan*/  XD_BLOCK_ADDR1_L ; 
 int /*<<< orphan*/  XD_BLOCK_ADDR2_H ; 
 int /*<<< orphan*/  XD_BLOCK_ADDR2_L ; 
 int /*<<< orphan*/  XD_BLOCK_STATUS ; 
 int /*<<< orphan*/  XD_CARD ; 
 int /*<<< orphan*/  XD_DAT ; 
 int XD_GPG ; 
 int XD_LATER_BBLK ; 
 int /*<<< orphan*/  XD_PAGE_CNT ; 
 int /*<<< orphan*/  XD_PAGE_STATUS ; 
 int /*<<< orphan*/  XD_PRG_ERROR ; 
 int /*<<< orphan*/  XD_RESERVED0 ; 
 int /*<<< orphan*/  XD_RESERVED1 ; 
 int /*<<< orphan*/  XD_RESERVED2 ; 
 int /*<<< orphan*/  XD_RESERVED3 ; 
 int /*<<< orphan*/  XD_RW_ADDR ; 
 int /*<<< orphan*/  XD_TO_ERROR ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int XD_WRITE_REDUNDANT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_xd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xd_assign_phy_addr (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xd_mark_bad_block(struct rtsx_chip *chip, u32 phy_blk)
{
	struct xd_info *xd_card = &chip->xd_card;
	int retval;
	u32 page_addr;
	u8 reg = 0;

	dev_dbg(rtsx_dev(chip), "mark block 0x%x as bad block\n", phy_blk);

	if (phy_blk == BLK_NOT_FOUND)
		return STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_STATUS, 0xFF, XD_GPG);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_STATUS, 0xFF, XD_LATER_BBLK);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_H, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR1_L, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR2_H, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_BLOCK_ADDR2_L, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED0, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED1, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED2, 0xFF, 0xFF);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_RESERVED3, 0xFF, 0xFF);

	page_addr = phy_blk << xd_card->block_shift;

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF,
		     xd_card->page_off + 1);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_WRITE_REDUNDANT);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 500);
	if (retval < 0) {
		rtsx_clear_xd_error(chip);
		rtsx_read_register(chip, XD_DAT, &reg);
		if (reg & PROGRAM_ERROR)
			xd_set_err_code(chip, XD_PRG_ERROR);
		else
			xd_set_err_code(chip, XD_TO_ERROR);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}