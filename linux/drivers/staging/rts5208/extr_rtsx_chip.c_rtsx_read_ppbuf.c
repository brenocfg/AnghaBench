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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPBUF_BASE2 ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 

int rtsx_read_ppbuf(struct rtsx_chip *chip, u8 *buf, int buf_len)
{
	int retval;
	int i, j;
	u16 reg_addr;
	u8 *ptr;

	if (!buf)
		return STATUS_ERROR;

	ptr = buf;
	reg_addr = PPBUF_BASE2;
	for (i = 0; i < buf_len / 256; i++) {
		rtsx_init_cmd(chip);

		for (j = 0; j < 256; j++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr++, 0, 0);

		retval = rtsx_send_cmd(chip, 0, 250);
		if (retval < 0)
			return STATUS_FAIL;

		memcpy(ptr, rtsx_get_cmd_data(chip), 256);
		ptr += 256;
	}

	if (buf_len % 256) {
		rtsx_init_cmd(chip);

		for (j = 0; j < buf_len % 256; j++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr++, 0, 0);

		retval = rtsx_send_cmd(chip, 0, 250);
		if (retval < 0)
			return STATUS_FAIL;
	}

	memcpy(ptr, rtsx_get_cmd_data(chip), buf_len % 256);

	return STATUS_SUCCESS;
}