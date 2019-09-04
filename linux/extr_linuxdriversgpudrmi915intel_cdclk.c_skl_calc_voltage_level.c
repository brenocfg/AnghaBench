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

__attribute__((used)) static u8 skl_calc_voltage_level(int cdclk)
{
	switch (cdclk) {
	default:
	case 308571:
	case 337500:
		return 0;
	case 450000:
	case 432000:
		return 1;
	case 540000:
		return 2;
	case 617143:
	case 675000:
		return 3;
	}
}