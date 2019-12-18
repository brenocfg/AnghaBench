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
typedef  size_t u8 ;
typedef  int u32 ;
struct ltc4151_data {int* regs; int shunt; } ;

/* Variables and functions */
#define  LTC4151_ADIN_H 130 
#define  LTC4151_SENSE_H 129 
#define  LTC4151_VIN_H 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static int ltc4151_get_value(struct ltc4151_data *data, u8 reg)
{
	u32 val;

	val = (data->regs[reg] << 4) + (data->regs[reg + 1] >> 4);

	switch (reg) {
	case LTC4151_ADIN_H:
		/* 500uV resolution. Convert to mV. */
		val = val * 500 / 1000;
		break;
	case LTC4151_SENSE_H:
		/*
		 * 20uV resolution. Convert to current as measured with
		 * a given sense resistor, in mA.
		 */
		val = val * 20 * 1000 / data->shunt;
		break;
	case LTC4151_VIN_H:
		/* 25 mV per increment */
		val = val * 25;
		break;
	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		val = 0;
		break;
	}

	return val;
}