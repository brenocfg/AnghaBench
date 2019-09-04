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
struct TYPE_2__ {int tuner_reset; } ;
struct tm6000_core {scalar_t__ tuner_type; TYPE_1__ gpio; int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_03_SET_GET_MCU_PIN ; 
 int /*<<< orphan*/  REQ_04_EN_DISABLE_MCU_INT ; 
 int /*<<< orphan*/  REQ_50_SET_START ; 
 int /*<<< orphan*/  REQ_51_SET_STOP ; 
#define  TM5600_BOARD_10MOONS_UT821 134 
#define  TM6010_BOARD_HAUPPAUGE_900H 133 
#define  TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE 132 
#define  TM6010_BOARD_TWINHAN_TU501 131 
 scalar_t__ TUNER_XC2028 ; 
#define  XC2028_I2C_FLUSH 130 
#define  XC2028_RESET_CLK 129 
#define  XC2028_TUNER_RESET 128 
 int /*<<< orphan*/  msleep (int) ; 
 int tm6000_i2c_reset (struct tm6000_core*,int) ; 
 int /*<<< orphan*/  tm6000_ir_wait (struct tm6000_core*,int) ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int,int) ; 

int tm6000_tuner_callback(void *ptr, int component, int command, int arg)
{
	int rc = 0;
	struct tm6000_core *dev = ptr;

	if (dev->tuner_type != TUNER_XC2028)
		return 0;

	switch (command) {
	case XC2028_RESET_CLK:
		tm6000_ir_wait(dev, 0);

		tm6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT,
					0x02, arg);
		msleep(10);
		rc = tm6000_i2c_reset(dev, 10);
		break;
	case XC2028_TUNER_RESET:
		/* Reset codes during load firmware */
		switch (arg) {
		case 0:
			/* newer tuner can faster reset */
			switch (dev->model) {
			case TM5600_BOARD_10MOONS_UT821:
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x01);
				msleep(10);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x00);
				msleep(10);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       0x300, 0x01);
				break;
			case TM6010_BOARD_HAUPPAUGE_900H:
			case TM6010_BOARD_TERRATEC_CINERGY_HYBRID_XE:
			case TM6010_BOARD_TWINHAN_TU501:
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(60);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				msleep(75);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(60);
				break;
			default:
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x00);
				msleep(130);
				tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
					       dev->gpio.tuner_reset, 0x01);
				msleep(130);
				break;
			}

			tm6000_ir_wait(dev, 1);
			break;
		case 1:
			tm6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT,
						0x02, 0x01);
			msleep(10);
			break;
		case 2:
			rc = tm6000_i2c_reset(dev, 100);
			break;
		}
		break;
	case XC2028_I2C_FLUSH:
		tm6000_set_reg(dev, REQ_50_SET_START, 0, 0);
		tm6000_set_reg(dev, REQ_51_SET_STOP, 0, 0);
		break;
	}
	return rc;
}