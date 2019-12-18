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
typedef  int u16 ;

/* Variables and functions */
 int SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES ; 

__attribute__((used)) static u16 si_get_cac_std_voltage_step(u16 max, u16 min)
{
	return ((max - min) + (SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES - 1)) /
		SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES;
}