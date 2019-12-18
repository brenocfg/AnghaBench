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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  power_led; } ;
struct tm6000_core {int model; TYPE_1__ gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_03_SET_GET_MCU_PIN ; 
#define  TM6010_BOARD_BEHOLD_VOYAGER 134 
#define  TM6010_BOARD_BEHOLD_VOYAGER_LITE 133 
#define  TM6010_BOARD_BEHOLD_WANDER 132 
#define  TM6010_BOARD_BEHOLD_WANDER_LITE 131 
#define  TM6010_BOARD_HAUPPAUGE_900H 130 
#define  TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE 129 
#define  TM6010_BOARD_TWINHAN_TU501 128 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void tm6000_flash_led(struct tm6000_core *dev, u8 state)
{
	/* Power LED unconfigured */
	if (!dev->gpio.power_led)
		return;

	/* ON Power LED */
	if (state) {
		switch (dev->model) {
		case TM6010_BOARD_HAUPPAUGE_900H:
		case TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		case TM6010_BOARD_TWINHAN_TU501:
			tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.power_led, 0x00);
			break;
		case TM6010_BOARD_BEHOLD_WANDER:
		case TM6010_BOARD_BEHOLD_VOYAGER:
		case TM6010_BOARD_BEHOLD_WANDER_LITE:
		case TM6010_BOARD_BEHOLD_VOYAGER_LITE:
			tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.power_led, 0x01);
			break;
		}
	}
	/* OFF Power LED */
	else {
		switch (dev->model) {
		case TM6010_BOARD_HAUPPAUGE_900H:
		case TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
		case TM6010_BOARD_TWINHAN_TU501:
			tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.power_led, 0x01);
			break;
		case TM6010_BOARD_BEHOLD_WANDER:
		case TM6010_BOARD_BEHOLD_VOYAGER:
		case TM6010_BOARD_BEHOLD_WANDER_LITE:
		case TM6010_BOARD_BEHOLD_VOYAGER_LITE:
			tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
				dev->gpio.power_led, 0x00);
			break;
		}
	}
}