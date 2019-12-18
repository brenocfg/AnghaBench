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
struct xd_info {int block_shift; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int BLK_NOT_FOUND ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int PROGRAM_ERROR ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  XD_CARD ; 
 int /*<<< orphan*/  XD_DAT ; 
 int XD_ERASE ; 
 int /*<<< orphan*/  XD_ERASE_ADDR ; 
 int /*<<< orphan*/  XD_ERASE_FAIL ; 
 int /*<<< orphan*/  XD_PRG_ERROR ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_xd_error (struct rtsx_chip*) ; 
 int* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xd_assign_phy_addr (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xd_mark_bad_block (struct rtsx_chip*,int) ; 
 int xd_reset_cmd (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xd_erase_block(struct rtsx_chip *chip, u32 phy_blk)
{
	struct xd_info *xd_card = &chip->xd_card;
	u32 page_addr;
	u8 reg = 0, *ptr;
	int i, retval;

	if (phy_blk == BLK_NOT_FOUND)
		return STATUS_FAIL;

	page_addr = phy_blk << xd_card->block_shift;

	for (i = 0; i < 3; i++) {
		rtsx_init_cmd(chip);

		xd_assign_phy_addr(chip, page_addr, XD_ERASE_ADDR);

		rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
			     XD_TRANSFER_START | XD_ERASE);
		rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
			     XD_TRANSFER_END, XD_TRANSFER_END);
		rtsx_add_cmd(chip, READ_REG_CMD, XD_DAT, 0, 0);

		retval = rtsx_send_cmd(chip, XD_CARD, 250);
		if (retval < 0) {
			rtsx_clear_xd_error(chip);
			rtsx_read_register(chip, XD_DAT, &reg);
			if (reg & PROGRAM_ERROR) {
				xd_mark_bad_block(chip, phy_blk);
				xd_set_err_code(chip, XD_PRG_ERROR);
				return STATUS_FAIL;
			}
			xd_set_err_code(chip, XD_ERASE_FAIL);
			retval = xd_reset_cmd(chip);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
			continue;
		}

		ptr = rtsx_get_cmd_data(chip) + 1;
		if (*ptr & PROGRAM_ERROR) {
			xd_mark_bad_block(chip, phy_blk);
			xd_set_err_code(chip, XD_PRG_ERROR);
			return STATUS_FAIL;
		}

		return STATUS_SUCCESS;
	}

	xd_mark_bad_block(chip, phy_blk);
	xd_set_err_code(chip, XD_ERASE_FAIL);
	return STATUS_FAIL;
}