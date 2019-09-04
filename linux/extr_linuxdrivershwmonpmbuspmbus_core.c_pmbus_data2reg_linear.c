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
typedef  long u16 ;
struct pmbus_sensor {scalar_t__ class; size_t page; } ;
struct pmbus_data {long* exponent; } ;
typedef  int s16 ;

/* Variables and functions */
 void* DIV_ROUND_CLOSEST (long,int) ; 
 long MAX_MANTISSA ; 
 long MIN_MANTISSA ; 
 scalar_t__ PSC_FAN ; 
 scalar_t__ PSC_POWER ; 
 scalar_t__ PSC_VOLTAGE_OUT ; 

__attribute__((used)) static u16 pmbus_data2reg_linear(struct pmbus_data *data,
				 struct pmbus_sensor *sensor, long val)
{
	s16 exponent = 0, mantissa;
	bool negative = false;

	/* simple case */
	if (val == 0)
		return 0;

	if (sensor->class == PSC_VOLTAGE_OUT) {
		/* LINEAR16 does not support negative voltages */
		if (val < 0)
			return 0;

		/*
		 * For a static exponents, we don't have a choice
		 * but to adjust the value to it.
		 */
		if (data->exponent[sensor->page] < 0)
			val <<= -data->exponent[sensor->page];
		else
			val >>= data->exponent[sensor->page];
		val = DIV_ROUND_CLOSEST(val, 1000);
		return val & 0xffff;
	}

	if (val < 0) {
		negative = true;
		val = -val;
	}

	/* Power is in uW. Convert to mW before converting. */
	if (sensor->class == PSC_POWER)
		val = DIV_ROUND_CLOSEST(val, 1000L);

	/*
	 * For simplicity, convert fan data to milli-units
	 * before calculating the exponent.
	 */
	if (sensor->class == PSC_FAN)
		val = val * 1000;

	/* Reduce large mantissa until it fits into 10 bit */
	while (val >= MAX_MANTISSA && exponent < 15) {
		exponent++;
		val >>= 1;
	}
	/* Increase small mantissa to improve precision */
	while (val < MIN_MANTISSA && exponent > -15) {
		exponent--;
		val <<= 1;
	}

	/* Convert mantissa from milli-units to units */
	mantissa = DIV_ROUND_CLOSEST(val, 1000);

	/* Ensure that resulting number is within range */
	if (mantissa > 0x3ff)
		mantissa = 0x3ff;

	/* restore sign */
	if (negative)
		mantissa = -mantissa;

	/* Convert to 5 bit exponent, 11 bit mantissa */
	return (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
}