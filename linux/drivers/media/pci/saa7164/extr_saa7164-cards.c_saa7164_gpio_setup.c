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
struct saa7164_dev {int board; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEBRIDGE_UNITID ; 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200 138 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_2 137 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_3 136 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_4 135 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2200_5 134 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2205 133 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250 132 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_2 131 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2250_3 130 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2255 129 
#define  SAA7164_BOARD_HAUPPAUGE_HVR2255proto 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa7164_api_clear_gpiobit (struct saa7164_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7164_api_set_gpiobit (struct saa7164_dev*,int /*<<< orphan*/ ,int) ; 

void saa7164_gpio_setup(struct saa7164_dev *dev)
{
	switch (dev->board) {
	case SAA7164_BOARD_HAUPPAUGE_HVR2200:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_3:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_4:
	case SAA7164_BOARD_HAUPPAUGE_HVR2200_5:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_2:
	case SAA7164_BOARD_HAUPPAUGE_HVR2250_3:
	case SAA7164_BOARD_HAUPPAUGE_HVR2255proto:
	case SAA7164_BOARD_HAUPPAUGE_HVR2255:
	case SAA7164_BOARD_HAUPPAUGE_HVR2205:
		/*
		HVR2200 / HVR2250
		GPIO 2: s5h1411 / tda10048-1 demod reset
		GPIO 3: s5h1411 / tda10048-2 demod reset
		GPIO 7: IRBlaster Zilog reset
		 */

		/* HVR2255
		 * GPIO 2: lgdg3306-1 demod reset
		 * GPIO 3: lgdt3306-2 demod reset
		 */

		/* HVR2205
		 * GPIO 2: si2168-1 demod reset
		 * GPIO 3: si2168-2 demod reset
		 */

		/* Reset parts by going in and out of reset */
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_clear_gpiobit(dev, PCIEBRIDGE_UNITID, 3);

		msleep(20);

		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 2);
		saa7164_api_set_gpiobit(dev, PCIEBRIDGE_UNITID, 3);
		break;
	}
}