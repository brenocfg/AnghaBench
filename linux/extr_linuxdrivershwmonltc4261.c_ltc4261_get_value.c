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
struct ltc4261_data {int* regs; } ;

/* Variables and functions */
#define  LTC4261_ADIN2_H 130 
#define  LTC4261_ADIN_H 129 
#define  LTC4261_SENSE_H 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static int ltc4261_get_value(struct ltc4261_data *data, u8 reg)
{
	u32 val;

	val = (data->regs[reg] << 2) + (data->regs[reg + 1] >> 6);

	switch (reg) {
	case LTC4261_ADIN_H:
	case LTC4261_ADIN2_H:
		/* 2.5mV resolution. Convert to mV. */
		val = val * 25 / 10;
		break;
	case LTC4261_SENSE_H:
		/*
		 * 62.5uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a different sense
		 * resistor is installed, calculate the actual current by
		 * dividing the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = val * 625 / 10;
		break;
	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		val = 0;
		break;
	}

	return val;
}