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
struct saa7134_dev {int board; } ;

/* Variables and functions */
#define  SAA7134_BOARD_AVERMEDIA_M733A 133 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1120 132 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1150 131 
#define  SAA7134_BOARD_KWORLD_PC150U 130 
#define  SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG 129 
#define  SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2 128 
 int saa7134_tda8290_18271_callback (struct saa7134_dev*,int,int) ; 
 int saa7134_tda8290_827x_callback (struct saa7134_dev*,int,int) ; 

__attribute__((used)) static int saa7134_tda8290_callback(struct saa7134_dev *dev,
				    int command, int arg)
{
	int ret;

	switch (dev->board) {
	case SAA7134_BOARD_HAUPPAUGE_HVR1150:
	case SAA7134_BOARD_HAUPPAUGE_HVR1120:
	case SAA7134_BOARD_AVERMEDIA_M733A:
	case SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
	case SAA7134_BOARD_KWORLD_PC150U:
	case SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
		/* tda8290 + tda18271 */
		ret = saa7134_tda8290_18271_callback(dev, command, arg);
		break;
	default:
		/* tda8290 + tda827x */
		ret = saa7134_tda8290_827x_callback(dev, command, arg);
		break;
	}
	return ret;
}