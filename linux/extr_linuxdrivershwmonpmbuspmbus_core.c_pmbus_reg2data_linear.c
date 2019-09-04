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
struct pmbus_sensor {scalar_t__ class; size_t page; int data; } ;
struct pmbus_data {int* exponent; } ;
typedef  long s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ PSC_FAN ; 
 scalar_t__ PSC_POWER ; 
 scalar_t__ PSC_VOLTAGE_OUT ; 

__attribute__((used)) static long pmbus_reg2data_linear(struct pmbus_data *data,
				  struct pmbus_sensor *sensor)
{
	s16 exponent;
	s32 mantissa;
	long val;

	if (sensor->class == PSC_VOLTAGE_OUT) {	/* LINEAR16 */
		exponent = data->exponent[sensor->page];
		mantissa = (u16) sensor->data;
	} else {				/* LINEAR11 */
		exponent = ((s16)sensor->data) >> 11;
		mantissa = ((s16)((sensor->data & 0x7ff) << 5)) >> 5;
	}

	val = mantissa;

	/* scale result to milli-units for all sensors except fans */
	if (sensor->class != PSC_FAN)
		val = val * 1000L;

	/* scale result to micro-units for power sensors */
	if (sensor->class == PSC_POWER)
		val = val * 1000L;

	if (exponent >= 0)
		val <<= exponent;
	else
		val >>= -exponent;

	return val;
}