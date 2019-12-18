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

/* Variables and functions */
 int /*<<< orphan*/  sony_pic_call1 (int) ; 

__attribute__((used)) static int type3_handle_irq(const u8 data_mask, const u8 ev)
{
	/*
	 * 0x31 could mean we have to take some extra action and wait for
	 * the next irq for some Type3 models, it will generate a new
	 * irq and we can read new data from the device:
	 *  - 0x5c and 0x5f requires 0xA0
	 *  - 0x61 requires 0xB3
	 */
	if (data_mask == 0x31) {
		if (ev == 0x5c || ev == 0x5f)
			sony_pic_call1(0xA0);
		else if (ev == 0x61)
			sony_pic_call1(0xB3);
		return 0;
	}
	return 1;
}