#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t type; } ;
struct bttv {TYPE_1__ c; int /*<<< orphan*/  has_radio_tuner; int /*<<< orphan*/  users; scalar_t__ opt_automute; } ;
struct TYPE_4__ {int gpiomute; int* gpiomux; int /*<<< orphan*/  gpiomask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DSTATUS ; 
 int BT848_DSTATUS_HLOC ; 
#define  BTTV_BOARD_VOODOOTV_200 129 
#define  BTTV_BOARD_VOODOOTV_FM 128 
 int /*<<< orphan*/ * audio_modes ; 
 int btread (int /*<<< orphan*/ ) ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,int /*<<< orphan*/ ) ; 
 int bttv_tda9880_setnorm (struct bttv*,int) ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  gpio_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_inout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audio_mux_gpio(struct bttv *btv, int input, int mute)
{
	int gpio_val, signal, mute_gpio;

	gpio_inout(bttv_tvcards[btv->c.type].gpiomask,
		   bttv_tvcards[btv->c.type].gpiomask);
	signal = btread(BT848_DSTATUS) & BT848_DSTATUS_HLOC;

	/* automute */
	mute_gpio = mute || (btv->opt_automute && (!signal || !btv->users)
				&& !btv->has_radio_tuner);

	if (mute_gpio)
		gpio_val = bttv_tvcards[btv->c.type].gpiomute;
	else
		gpio_val = bttv_tvcards[btv->c.type].gpiomux[input];

	switch (btv->c.type) {
	case BTTV_BOARD_VOODOOTV_FM:
	case BTTV_BOARD_VOODOOTV_200:
		gpio_val = bttv_tda9880_setnorm(btv, gpio_val);
		break;

	default:
		gpio_bits(bttv_tvcards[btv->c.type].gpiomask, gpio_val);
	}

	if (bttv_gpio)
		bttv_gpio_tracking(btv, audio_modes[mute_gpio ? 4 : input]);
}