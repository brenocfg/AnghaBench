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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t smu8_convert_8Bit_index_to_voltage(
			struct pp_hwmgr *hwmgr, uint16_t voltage)
{
	return 6200 - (voltage * 25);
}