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
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static bool edma_is_memcpy_channel(int ch_num, s32 *memcpy_channels)
{
	if (!memcpy_channels)
		return false;
	while (*memcpy_channels != -1) {
		if (*memcpy_channels == ch_num)
			return true;
		memcpy_channels++;
	}
	return false;
}