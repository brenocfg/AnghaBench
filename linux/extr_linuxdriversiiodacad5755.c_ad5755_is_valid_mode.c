#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ad5755_state {TYPE_1__* chip_info; } ;
typedef  enum ad5755_mode { ____Placeholder_ad5755_mode } ad5755_mode ;
struct TYPE_2__ {int has_voltage_out; } ;

/* Variables and functions */
#define  AD5755_MODE_CURRENT_0mA_20mA 134 
#define  AD5755_MODE_CURRENT_0mA_24mA 133 
#define  AD5755_MODE_CURRENT_4mA_20mA 132 
#define  AD5755_MODE_VOLTAGE_0V_10V 131 
#define  AD5755_MODE_VOLTAGE_0V_5V 130 
#define  AD5755_MODE_VOLTAGE_PLUSMINUS_10V 129 
#define  AD5755_MODE_VOLTAGE_PLUSMINUS_5V 128 

__attribute__((used)) static bool ad5755_is_valid_mode(struct ad5755_state *st, enum ad5755_mode mode)
{
	switch (mode) {
	case AD5755_MODE_VOLTAGE_0V_5V:
	case AD5755_MODE_VOLTAGE_0V_10V:
	case AD5755_MODE_VOLTAGE_PLUSMINUS_5V:
	case AD5755_MODE_VOLTAGE_PLUSMINUS_10V:
		return st->chip_info->has_voltage_out;
	case AD5755_MODE_CURRENT_4mA_20mA:
	case AD5755_MODE_CURRENT_0mA_20mA:
	case AD5755_MODE_CURRENT_0mA_24mA:
		return true;
	default:
		return false;
	}
}