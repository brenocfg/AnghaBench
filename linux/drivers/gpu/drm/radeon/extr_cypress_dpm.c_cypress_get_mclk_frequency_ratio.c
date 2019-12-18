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
typedef  int u32 ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_BARTS ; 

u8 cypress_get_mclk_frequency_ratio(struct radeon_device *rdev,
				    u32 memory_clock, bool strobe_mode)
{
	u8 mc_para_index;

	if (rdev->family >= CHIP_BARTS) {
		if (strobe_mode) {
			if (memory_clock < 10000)
				mc_para_index = 0x00;
			else if (memory_clock > 47500)
				mc_para_index = 0x0f;
			else
				mc_para_index = (u8)((memory_clock - 10000) / 2500);
		} else {
			if (memory_clock < 65000)
				mc_para_index = 0x00;
			else if (memory_clock > 135000)
				mc_para_index = 0x0f;
			else
				mc_para_index = (u8)((memory_clock - 60000) / 5000);
		}
	} else {
		if (strobe_mode) {
			if (memory_clock < 10000)
				mc_para_index = 0x00;
			else if (memory_clock > 47500)
				mc_para_index = 0x0f;
			else
				mc_para_index = (u8)((memory_clock - 10000) / 2500);
		} else {
			if (memory_clock < 40000)
				mc_para_index = 0x00;
			else if (memory_clock > 115000)
				mc_para_index = 0x0f;
			else
				mc_para_index = (u8)((memory_clock - 40000) / 5000);
		}
	}
	return mc_para_index;
}