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
typedef  long s16 ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (long,int) ; 
#define  INA209_BUS_VOLTAGE 146 
#define  INA209_BUS_VOLTAGE_MAX_PEAK 145 
#define  INA209_BUS_VOLTAGE_MIN_PEAK 144 
#define  INA209_BUS_VOLTAGE_OVER_LIMIT 143 
#define  INA209_BUS_VOLTAGE_OVER_WARN 142 
#define  INA209_BUS_VOLTAGE_UNDER_LIMIT 141 
#define  INA209_BUS_VOLTAGE_UNDER_WARN 140 
#define  INA209_CRITICAL_DAC_NEG 139 
#define  INA209_CRITICAL_DAC_POS 138 
#define  INA209_CURRENT 137 
#define  INA209_POWER 136 
#define  INA209_POWER_OVER_LIMIT 135 
#define  INA209_POWER_PEAK 134 
#define  INA209_POWER_WARN 133 
#define  INA209_SHUNT_VOLTAGE 132 
#define  INA209_SHUNT_VOLTAGE_NEG_PEAK 131 
#define  INA209_SHUNT_VOLTAGE_NEG_WARN 130 
#define  INA209_SHUNT_VOLTAGE_POS_PEAK 129 
#define  INA209_SHUNT_VOLTAGE_POS_WARN 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static long ina209_from_reg(const u8 reg, const u16 val)
{
	switch (reg) {
	case INA209_SHUNT_VOLTAGE:
	case INA209_SHUNT_VOLTAGE_POS_PEAK:
	case INA209_SHUNT_VOLTAGE_NEG_PEAK:
	case INA209_SHUNT_VOLTAGE_POS_WARN:
	case INA209_SHUNT_VOLTAGE_NEG_WARN:
		/* LSB=10 uV. Convert to mV. */
		return DIV_ROUND_CLOSEST((s16)val, 100);

	case INA209_BUS_VOLTAGE:
	case INA209_BUS_VOLTAGE_MAX_PEAK:
	case INA209_BUS_VOLTAGE_MIN_PEAK:
	case INA209_BUS_VOLTAGE_OVER_WARN:
	case INA209_BUS_VOLTAGE_UNDER_WARN:
	case INA209_BUS_VOLTAGE_OVER_LIMIT:
	case INA209_BUS_VOLTAGE_UNDER_LIMIT:
		/* LSB=4 mV, last 3 bits unused */
		return (val >> 3) * 4;

	case INA209_CRITICAL_DAC_POS:
		/* LSB=1 mV, in the upper 8 bits */
		return val >> 8;

	case INA209_CRITICAL_DAC_NEG:
		/* LSB=1 mV, in the upper 8 bits */
		return -1 * (val >> 8);

	case INA209_POWER:
	case INA209_POWER_PEAK:
	case INA209_POWER_WARN:
	case INA209_POWER_OVER_LIMIT:
		/* LSB=20 mW. Convert to uW */
		return val * 20 * 1000L;

	case INA209_CURRENT:
		/* LSB=1 mA (selected). Is in mA */
		return (s16)val;
	}

	/* programmer goofed */
	WARN_ON_ONCE(1);
	return 0;
}