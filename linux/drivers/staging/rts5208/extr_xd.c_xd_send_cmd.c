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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  XD_CARD ; 
 int /*<<< orphan*/  XD_DAT ; 
 int XD_SET_CMD ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xd_send_cmd(struct rtsx_chip *chip, u8 cmd)
{
	int retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_DAT, 0xFF, cmd);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_SET_CMD);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END, XD_TRANSFER_END);

	retval = rtsx_send_cmd(chip, XD_CARD, 200);
	if (retval < 0)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}