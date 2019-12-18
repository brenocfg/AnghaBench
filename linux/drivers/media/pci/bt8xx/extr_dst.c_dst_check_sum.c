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
typedef  size_t u32 ;

/* Variables and functions */

u8 dst_check_sum(u8 *buf, u32 len)
{
	u32 i;
	u8 val = 0;
	if (!len)
		return 0;
	for (i = 0; i < len; i++) {
		val += buf[i];
	}
	return ((~val) + 1);
}