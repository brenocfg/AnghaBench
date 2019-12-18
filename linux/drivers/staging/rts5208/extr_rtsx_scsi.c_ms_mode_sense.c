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
typedef  scalar_t__ u8 ;
struct ms_info {int /*<<< orphan*/  raw_sys_info; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 scalar_t__ CHK_MSXC (struct ms_info*) ; 
 scalar_t__ MODE_SENSE ; 
 scalar_t__ MODE_SENSE_10 ; 
 scalar_t__ check_card_ready (struct rtsx_chip*,int) ; 
 scalar_t__ check_card_wp (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ms_mode_sense(struct rtsx_chip *chip, u8 cmd,
			  int lun, u8 *buf, int buf_len)
{
	struct ms_info *ms_card = &chip->ms_card;
	int sys_info_offset;
	int data_size = buf_len;
	bool support_format = false;
	int i = 0;

	if (cmd == MODE_SENSE) {
		sys_info_offset = 8;
		if (data_size > 0x68)
			data_size = 0x68;

		buf[i++] = 0x67;  /* Mode Data Length */
	} else {
		sys_info_offset = 12;
		if (data_size > 0x6C)
			data_size = 0x6C;

		buf[i++] = 0x00;  /* Mode Data Length (MSB) */
		buf[i++] = 0x6A;  /* Mode Data Length (LSB) */
	}

	/* Medium Type Code */
	if (check_card_ready(chip, lun)) {
		if (CHK_MSXC(ms_card)) {
			support_format = true;
			buf[i++] = 0x40;
		} else if (CHK_MSPRO(ms_card)) {
			support_format = true;
			buf[i++] = 0x20;
		} else {
			buf[i++] = 0x10;
		}

		/* WP */
		if (check_card_wp(chip, lun))
			buf[i++] = 0x80;
		else
			buf[i++] = 0x00;

	} else {
		buf[i++] = 0x00;	/* MediaType */
		buf[i++] = 0x00;	/* WP */
	}

	buf[i++] = 0x00;		/* Reserved */

	if (cmd == MODE_SENSE_10) {
		buf[i++] = 0x00;  /* Reserved */
		buf[i++] = 0x00;  /* Block descriptor length(MSB) */
		buf[i++] = 0x00;  /* Block descriptor length(LSB) */

		/* The Following Data is the content of "Page 0x20" */
		if (data_size >= 9)
			buf[i++] = 0x20;		/* Page Code */
		if (data_size >= 10)
			buf[i++] = 0x62;		/* Page Length */
		if (data_size >= 11)
			buf[i++] = 0x00;		/* No Access Control */
		if (data_size >= 12) {
			if (support_format)
				buf[i++] = 0xC0;	/* SF, SGM */
			else
				buf[i++] = 0x00;
		}
	} else {
		/* The Following Data is the content of "Page 0x20" */
		if (data_size >= 5)
			buf[i++] = 0x20;		/* Page Code */
		if (data_size >= 6)
			buf[i++] = 0x62;		/* Page Length */
		if (data_size >= 7)
			buf[i++] = 0x00;		/* No Access Control */
		if (data_size >= 8) {
			if (support_format)
				buf[i++] = 0xC0;	/* SF, SGM */
			else
				buf[i++] = 0x00;
		}
	}

	if (data_size > sys_info_offset) {
		/* 96 Bytes Attribute Data */
		int len = data_size - sys_info_offset;

		len = (len < 96) ? len : 96;

		memcpy(buf + sys_info_offset, ms_card->raw_sys_info, len);
	}
}