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
struct ltc4215_data {int* regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t LTC4215_SENSE ; 
 struct ltc4215_data* ltc4215_update_device (struct device*) ; 

__attribute__((used)) static unsigned int ltc4215_get_current(struct device *dev)
{
	struct ltc4215_data *data = ltc4215_update_device(dev);

	/*
	 * The strange looking conversions that follow are fixed-point
	 * math, since we cannot do floating point in the kernel.
	 *
	 * Step 1: convert sense register to microVolts
	 * Step 2: convert voltage to milliAmperes
	 *
	 * If you play around with the V=IR equation, you come up with
	 * the following: X uV / Y mOhm == Z mA
	 *
	 * With the resistors that are fractions of a milliOhm, we multiply
	 * the voltage and resistance by 10, to shift the decimal point.
	 * Now we can use the normal division operator again.
	 */

	/* Calculate voltage in microVolts (151 uV per increment) */
	const unsigned int voltage = data->regs[LTC4215_SENSE] * 151;

	/* Calculate current in milliAmperes (4 milliOhm sense resistor) */
	const unsigned int curr = voltage / 4;

	return curr;
}