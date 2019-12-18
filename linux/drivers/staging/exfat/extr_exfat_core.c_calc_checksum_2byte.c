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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */
#define  CS_DIR_ENTRY 128 

u16 calc_checksum_2byte(void *data, s32 len, u16 chksum, s32 type)
{
	int i;
	u8 *c = (u8 *)data;

	switch (type) {
	case CS_DIR_ENTRY:
		for (i = 0; i < len; i++, c++) {
			if ((i == 2) || (i == 3))
				continue;
			chksum = (((chksum & 1) << 15) |
				  ((chksum & 0xFFFE) >> 1)) + (u16)*c;
		}
		break;
	default
			:
		for (i = 0; i < len; i++, c++)
			chksum = (((chksum & 1) << 15) |
				  ((chksum & 0xFFFE) >> 1)) + (u16)*c;
	}

	return chksum;
}