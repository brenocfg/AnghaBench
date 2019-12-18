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
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  QCAFRM_HEADER_LEN ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 

u16
qcafrm_create_header(u8 *buf, u16 length)
{
	__le16 len;

	if (!buf)
		return 0;

	len = cpu_to_le16(length);

	buf[0] = 0xAA;
	buf[1] = 0xAA;
	buf[2] = 0xAA;
	buf[3] = 0xAA;
	buf[4] = len & 0xff;
	buf[5] = (len >> 8) & 0xff;
	buf[6] = 0;
	buf[7] = 0;

	return QCAFRM_HEADER_LEN;
}