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
typedef  enum ad5755_mode { ____Placeholder_ad5755_mode } ad5755_mode ;

/* Variables and functions */
#define  AD5755_MODE_VOLTAGE_0V_10V 131 
#define  AD5755_MODE_VOLTAGE_0V_5V 130 
#define  AD5755_MODE_VOLTAGE_PLUSMINUS_10V 129 
#define  AD5755_MODE_VOLTAGE_PLUSMINUS_5V 128 

__attribute__((used)) static bool ad5755_is_voltage_mode(enum ad5755_mode mode)
{
	switch (mode) {
	case AD5755_MODE_VOLTAGE_0V_5V:
	case AD5755_MODE_VOLTAGE_0V_10V:
	case AD5755_MODE_VOLTAGE_PLUSMINUS_5V:
	case AD5755_MODE_VOLTAGE_PLUSMINUS_10V:
		return true;
	default:
		return false;
	}
}