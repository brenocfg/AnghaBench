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
typedef  int u8 ;
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAA7134_MISC_VGATE_MSB ; 
 int /*<<< orphan*/  SAA7134_VGATE_START ; 
 int /*<<< orphan*/  SAA7134_VGATE_STOP ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL3 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL6 ; 
 int /*<<< orphan*/  saa7134_set_gpio (struct saa7134_dev*,int,int) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int saa7134_tda8290_827x_callback(struct saa7134_dev *dev,
					 int command, int arg)
{
	u8 sync_control;

	switch (command) {
	case 0: /* switch LNA gain through GPIO 22*/
		saa7134_set_gpio(dev, 22, arg) ;
		break;
	case 1: /* vsync output at GPIO22. 50 / 60Hz */
		saa_andorb(SAA7134_VIDEO_PORT_CTRL3, 0x80, 0x80);
		saa_andorb(SAA7134_VIDEO_PORT_CTRL6, 0x0f, 0x03);
		if (arg == 1)
			sync_control = 11;
		else
			sync_control = 17;
		saa_writeb(SAA7134_VGATE_START, sync_control);
		saa_writeb(SAA7134_VGATE_STOP, sync_control + 1);
		saa_andorb(SAA7134_MISC_VGATE_MSB, 0x03, 0x00);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}