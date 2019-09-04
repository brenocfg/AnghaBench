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

/* Variables and functions */

__attribute__((used)) static unsigned long f_extend(unsigned long address)
{
#ifdef CONFIG_64BIT
	if(unlikely(parisc_narrow_firmware)) {
		if((address & 0xff000000) == 0xf0000000)
			return 0xf0f0f0f000000000UL | (u32)address;

		if((address & 0xf0000000) == 0xf0000000)
			return 0xffffffff00000000UL | (u32)address;
	}
#endif
	return address;
}