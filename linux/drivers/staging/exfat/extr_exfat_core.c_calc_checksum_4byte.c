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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
#define  CS_PBR_SECTOR 128 

u32 calc_checksum_4byte(void *data, s32 len, u32 chksum, s32 type)
{
	int i;
	u8 *c = (u8 *)data;

	switch (type) {
	case CS_PBR_SECTOR:
		for (i = 0; i < len; i++, c++) {
			if ((i == 106) || (i == 107) || (i == 112))
				continue;
			chksum = (((chksum & 1) << 31) |
				  ((chksum & 0xFFFFFFFE) >> 1)) + (u32)*c;
		}
		break;
	default
			:
		for (i = 0; i < len; i++, c++)
			chksum = (((chksum & 1) << 31) |
				  ((chksum & 0xFFFFFFFE) >> 1)) + (u32)*c;
	}

	return chksum;
}