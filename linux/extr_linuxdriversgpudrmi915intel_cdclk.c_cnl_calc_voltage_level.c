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

__attribute__((used)) static u8 cnl_calc_voltage_level(int cdclk)
{
	switch (cdclk) {
	default:
	case 168000:
		return 0;
	case 336000:
		return 1;
	case 528000:
		return 2;
	}
}