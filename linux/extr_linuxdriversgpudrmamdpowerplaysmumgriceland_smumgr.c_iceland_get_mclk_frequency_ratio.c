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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t iceland_get_mclk_frequency_ratio(uint32_t memory_clock,
		bool strobe_mode)
{
	uint8_t mc_para_index;

	if (strobe_mode) {
		if (memory_clock < 12500) {
			mc_para_index = 0x00;
		} else if (memory_clock > 47500) {
			mc_para_index = 0x0f;
		} else {
			mc_para_index = (uint8_t)((memory_clock - 10000) / 2500);
		}
	} else {
		if (memory_clock < 65000) {
			mc_para_index = 0x00;
		} else if (memory_clock > 135000) {
			mc_para_index = 0x0f;
		} else {
			mc_para_index = (uint8_t)((memory_clock - 60000) / 5000);
		}
	}

	return mc_para_index;
}