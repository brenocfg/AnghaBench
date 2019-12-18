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
struct ltc4215_data {size_t* regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  LTC4215_ADIN 130 
#define  LTC4215_SENSE 129 
#define  LTC4215_SOURCE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ltc4215_data* ltc4215_update_device (struct device*) ; 

__attribute__((used)) static int ltc4215_get_voltage(struct device *dev, u8 reg)
{
	struct ltc4215_data *data = ltc4215_update_device(dev);
	const u8 regval = data->regs[reg];
	u32 voltage = 0;

	switch (reg) {
	case LTC4215_SENSE:
		/* 151 uV per increment */
		voltage = regval * 151 / 1000;
		break;
	case LTC4215_SOURCE:
		/* 60.5 mV per increment */
		voltage = regval * 605 / 10;
		break;
	case LTC4215_ADIN:
		/*
		 * The ADIN input is divided by 12.5, and has 4.82 mV
		 * per increment, so we have the additional multiply
		 */
		voltage = regval * 482 * 125 / 1000;
		break;
	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		break;
	}

	return voltage;
}