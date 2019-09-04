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
typedef  int u32 ;
struct cx18 {int hw_flags; TYPE_1__* card; void* sd_extmux; void* sd_av; } ;
struct TYPE_2__ {int hw_all; int const hw_muxer; } ;

/* Variables and functions */
#define  CX18_HW_418_AV 132 
#define  CX18_HW_DVB 131 
#define  CX18_HW_GPIO_MUX 130 
#define  CX18_HW_GPIO_RESET_CTRL 129 
#define  CX18_HW_TVEEPROM 128 
 void* cx18_find_hw (struct cx18*,int const) ; 
 int /*<<< orphan*/  cx18_gpio_register (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_i2c_register (struct cx18*,int) ; 

__attribute__((used)) static void cx18_init_subdevs(struct cx18 *cx)
{
	u32 hw = cx->card->hw_all;
	u32 device;
	int i;

	for (i = 0, device = 1; i < 32; i++, device <<= 1) {

		if (!(device & hw))
			continue;

		switch (device) {
		case CX18_HW_DVB:
		case CX18_HW_TVEEPROM:
			/* These subordinate devices do not use probing */
			cx->hw_flags |= device;
			break;
		case CX18_HW_418_AV:
			/* The A/V decoder gets probed earlier to set PLLs */
			/* Just note that the card uses it (i.e. has analog) */
			cx->hw_flags |= device;
			break;
		case CX18_HW_GPIO_RESET_CTRL:
			/*
			 * The Reset Controller gets probed and added to
			 * hw_flags earlier for i2c adapter/bus initialization
			 */
			break;
		case CX18_HW_GPIO_MUX:
			if (cx18_gpio_register(cx, device) == 0)
				cx->hw_flags |= device;
			break;
		default:
			if (cx18_i2c_register(cx, i) == 0)
				cx->hw_flags |= device;
			break;
		}
	}

	if (cx->hw_flags & CX18_HW_418_AV)
		cx->sd_av = cx18_find_hw(cx, CX18_HW_418_AV);

	if (cx->card->hw_muxer != 0)
		cx->sd_extmux = cx18_find_hw(cx, cx->card->hw_muxer);
}