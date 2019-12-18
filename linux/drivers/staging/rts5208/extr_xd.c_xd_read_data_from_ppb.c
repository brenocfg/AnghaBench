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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ PPBUF_BASE2 ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_clear_xd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xd_read_data_from_ppb(struct rtsx_chip *chip, int offset,
				 u8 *buf, int buf_len)
{
	int retval, i;

	if (!buf || (buf_len < 0))
		return STATUS_FAIL;

	rtsx_init_cmd(chip);

	for (i = 0; i < buf_len; i++)
		rtsx_add_cmd(chip, READ_REG_CMD, PPBUF_BASE2 + offset + i,
			     0, 0);

	retval = rtsx_send_cmd(chip, 0, 250);
	if (retval < 0) {
		rtsx_clear_xd_error(chip);
		return STATUS_FAIL;
	}

	memcpy(buf, rtsx_get_cmd_data(chip), buf_len);

	return STATUS_SUCCESS;
}