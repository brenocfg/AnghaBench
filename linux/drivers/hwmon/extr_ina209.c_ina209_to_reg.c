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
typedef  int u16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (long,int) ; 
 int EACCES ; 
#define  INA209_BUS_VOLTAGE_OVER_LIMIT 137 
#define  INA209_BUS_VOLTAGE_OVER_WARN 136 
#define  INA209_BUS_VOLTAGE_UNDER_LIMIT 135 
#define  INA209_BUS_VOLTAGE_UNDER_WARN 134 
#define  INA209_CRITICAL_DAC_NEG 133 
#define  INA209_CRITICAL_DAC_POS 132 
#define  INA209_POWER_OVER_LIMIT 131 
#define  INA209_POWER_WARN 130 
#define  INA209_SHUNT_VOLTAGE_NEG_WARN 129 
#define  INA209_SHUNT_VOLTAGE_POS_WARN 128 
 int clamp_val (long,int,int) ; 

__attribute__((used)) static int ina209_to_reg(u8 reg, u16 old, long val)
{
	switch (reg) {
	case INA209_SHUNT_VOLTAGE_POS_WARN:
	case INA209_SHUNT_VOLTAGE_NEG_WARN:
		/* Limit to +- 320 mV, 10 uV LSB */
		return clamp_val(val, -320, 320) * 100;

	case INA209_BUS_VOLTAGE_OVER_WARN:
	case INA209_BUS_VOLTAGE_UNDER_WARN:
	case INA209_BUS_VOLTAGE_OVER_LIMIT:
	case INA209_BUS_VOLTAGE_UNDER_LIMIT:
		/*
		 * Limit to 0-32000 mV, 4 mV LSB
		 *
		 * The last three bits aren't part of the value, but we'll
		 * preserve them in their original state.
		 */
		return (DIV_ROUND_CLOSEST(clamp_val(val, 0, 32000), 4) << 3)
		  | (old & 0x7);

	case INA209_CRITICAL_DAC_NEG:
		/*
		 * Limit to -255-0 mV, 1 mV LSB
		 * Convert the value to a positive value for the register
		 *
		 * The value lives in the top 8 bits only, be careful
		 * and keep original value of other bits.
		 */
		return (clamp_val(-val, 0, 255) << 8) | (old & 0xff);

	case INA209_CRITICAL_DAC_POS:
		/*
		 * Limit to 0-255 mV, 1 mV LSB
		 *
		 * The value lives in the top 8 bits only, be careful
		 * and keep original value of other bits.
		 */
		return (clamp_val(val, 0, 255) << 8) | (old & 0xff);

	case INA209_POWER_WARN:
	case INA209_POWER_OVER_LIMIT:
		/* 20 mW LSB */
		return DIV_ROUND_CLOSEST(val, 20 * 1000);
	}

	/* Other registers are read-only, return access error */
	return -EACCES;
}