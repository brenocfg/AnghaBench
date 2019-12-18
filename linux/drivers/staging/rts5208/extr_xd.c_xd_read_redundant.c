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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  XD_CARD ; 
 scalar_t__ XD_PAGE_STATUS ; 
 int /*<<< orphan*/  XD_PARITY ; 
 int XD_READ_REDUNDANT ; 
 scalar_t__ XD_RESERVED0 ; 
 int /*<<< orphan*/  XD_RW_ADDR ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xd_assign_phy_addr (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xd_read_redundant(struct rtsx_chip *chip, u32 page_addr,
			     u8 *buf, int buf_len)
{
	int retval, i;

	rtsx_init_cmd(chip);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER,
		     0xFF, XD_TRANSFER_START | XD_READ_REDUNDANT);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	for (i = 0; i < 6; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, (u16)(XD_PAGE_STATUS + i),
			     0, 0);
	for (i = 0; i < 4; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, (u16)(XD_RESERVED0 + i),
			     0, 0);
	rtsx_add_cmd(chip, READ_REG_CMD, XD_PARITY, 0, 0);

	retval = rtsx_send_cmd(chip, XD_CARD, 500);
	if (retval < 0)
		return STATUS_FAIL;

	if (buf && buf_len) {
		u8 *ptr = rtsx_get_cmd_data(chip) + 1;

		if (buf_len > 11)
			buf_len = 11;
		memcpy(buf, ptr, buf_len);
	}

	return STATUS_SUCCESS;
}