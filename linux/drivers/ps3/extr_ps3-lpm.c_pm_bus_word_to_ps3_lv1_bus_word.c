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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 pm_bus_word_to_ps3_lv1_bus_word(u8 word)
{

	switch (word) {
	case 1:
		return 0xF000;
	case 2:
		return 0x0F00;
	case 4:
		return 0x00F0;
	case 8:
	default:
		return 0x000F;
	}
}