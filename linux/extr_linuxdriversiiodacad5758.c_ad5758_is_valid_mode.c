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
typedef  enum ad5758_dc_dc_mode { ____Placeholder_ad5758_dc_dc_mode } ad5758_dc_dc_mode ;

/* Variables and functions */
#define  AD5758_DCDC_MODE_DPC_CURRENT 130 
#define  AD5758_DCDC_MODE_DPC_VOLTAGE 129 
#define  AD5758_DCDC_MODE_PPC_CURRENT 128 

__attribute__((used)) static bool ad5758_is_valid_mode(enum ad5758_dc_dc_mode mode)
{
	switch (mode) {
	case AD5758_DCDC_MODE_DPC_CURRENT:
	case AD5758_DCDC_MODE_DPC_VOLTAGE:
	case AD5758_DCDC_MODE_PPC_CURRENT:
		return true;
	default:
		return false;
	}
}