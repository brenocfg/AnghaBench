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
struct TYPE_2__ {int /*<<< orphan*/  tuner_reset; } ;
struct tm6000_core {scalar_t__ tuner_type; TYPE_1__ gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_03_SET_GET_MCU_PIN ; 
 scalar_t__ TUNER_XC5000 ; 
#define  XC5000_TUNER_RESET 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int tm6000_xc5000_callback(void *ptr, int component, int command, int arg)
{
	int rc = 0;
	struct tm6000_core *dev = ptr;

	if (dev->tuner_type != TUNER_XC5000)
		return 0;

	switch (command) {
	case XC5000_TUNER_RESET:
		tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x01);
		msleep(15);
		tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x00);
		msleep(15);
		tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			       dev->gpio.tuner_reset, 0x01);
		break;
	}
	return rc;
}