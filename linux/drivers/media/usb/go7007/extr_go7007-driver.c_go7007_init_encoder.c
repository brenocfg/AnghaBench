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
struct go7007 {int board_id; TYPE_1__* board_info; } ;
struct TYPE_2__ {int audio_flags; } ;

/* Variables and functions */
 int GO7007_AUDIO_I2S_MASTER ; 
#define  GO7007_BOARDID_ADLINK_MPG24 130 
#define  GO7007_BOARDID_ADS_USBAV_709 129 
#define  GO7007_BOARDID_MATRIX_REV 128 
 int /*<<< orphan*/  go7007_write_addr (struct go7007*,int,int) ; 

__attribute__((used)) static int go7007_init_encoder(struct go7007 *go)
{
	if (go->board_info->audio_flags & GO7007_AUDIO_I2S_MASTER) {
		go7007_write_addr(go, 0x1000, 0x0811);
		go7007_write_addr(go, 0x1000, 0x0c11);
	}
	switch (go->board_id) {
	case GO7007_BOARDID_MATRIX_REV:
		/* Set GPIO pin 0 to be an output (audio clock control) */
		go7007_write_addr(go, 0x3c82, 0x0001);
		go7007_write_addr(go, 0x3c80, 0x00fe);
		break;
	case GO7007_BOARDID_ADLINK_MPG24:
		/* set GPIO5 to be an output, currently low */
		go7007_write_addr(go, 0x3c82, 0x0000);
		go7007_write_addr(go, 0x3c80, 0x00df);
		break;
	case GO7007_BOARDID_ADS_USBAV_709:
		/* GPIO pin 0: audio clock control */
		/*      pin 2: TW9906 reset */
		/*      pin 3: capture LED */
		go7007_write_addr(go, 0x3c82, 0x000d);
		go7007_write_addr(go, 0x3c80, 0x00f2);
		break;
	}
	return 0;
}