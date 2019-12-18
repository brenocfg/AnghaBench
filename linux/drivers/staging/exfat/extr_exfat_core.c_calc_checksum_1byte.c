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
typedef  int s32 ;

/* Variables and functions */

u8 calc_checksum_1byte(void *data, s32 len, u8 chksum)
{
	int i;
	u8 *c = (u8 *)data;

	for (i = 0; i < len; i++, c++)
		chksum = (((chksum & 1) << 7) | ((chksum & 0xFE) >> 1)) + *c;

	return chksum;
}