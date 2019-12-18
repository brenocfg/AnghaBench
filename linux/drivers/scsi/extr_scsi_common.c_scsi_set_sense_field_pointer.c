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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ scsi_sense_desc_find (int*,int,int) ; 

int scsi_set_sense_field_pointer(u8 *buf, int buf_len, u16 fp, u8 bp, bool cd)
{
	u8 *ucp, len;

	if ((buf[0] & 0x7f) == 0x72) {
		len = buf[7];
		ucp = (char *)scsi_sense_desc_find(buf, len + 8, 2);
		if (!ucp) {
			buf[7] = len + 8;
			ucp = buf + 8 + len;
		}

		if (buf_len < len + 8)
			/* Not enough room for info */
			return -EINVAL;

		ucp[0] = 2;
		ucp[1] = 6;
		ucp[4] = 0x80; /* Valid bit */
		if (cd)
			ucp[4] |= 0x40;
		if (bp < 0x8)
			ucp[4] |= 0x8 | bp;
		put_unaligned_be16(fp, &ucp[5]);
	} else if ((buf[0] & 0x7f) == 0x70) {
		len = buf[7];
		if (len < 18)
			buf[7] = 18;

		buf[15] = 0x80;
		if (cd)
			buf[15] |= 0x40;
		if (bp < 0x8)
			buf[15] |= 0x8 | bp;
		put_unaligned_be16(fp, &buf[16]);
	}

	return 0;
}