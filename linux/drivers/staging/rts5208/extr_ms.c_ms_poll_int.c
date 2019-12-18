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
 int /*<<< orphan*/  MS_CARD ; 
 int /*<<< orphan*/  MS_INT_CED ; 
 int MS_INT_ERR ; 
 int /*<<< orphan*/  MS_TRANS_CFG ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ms_poll_int(struct rtsx_chip *chip)
{
	int retval;
	u8 val;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, CHECK_REG_CMD, MS_TRANS_CFG, MS_INT_CED, MS_INT_CED);

	retval = rtsx_send_cmd(chip, MS_CARD, 5000);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	val = *rtsx_get_cmd_data(chip);
	if (val & MS_INT_ERR)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}