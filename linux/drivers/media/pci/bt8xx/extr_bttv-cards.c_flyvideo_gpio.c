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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {int tuner_type; int has_radio; int /*<<< orphan*/  audio_mode_gpio; TYPE_1__ c; } ;

/* Variables and functions */
 int TUNER_ABSENT ; 
 int UNSET ; 
 int /*<<< orphan*/  gpio_inout (int,int /*<<< orphan*/ ) ; 
 int gpio_read () ; 
 int /*<<< orphan*/  lt9415_audio ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void flyvideo_gpio(struct bttv *btv)
{
	int gpio, has_remote, has_radio, is_capture_only;
	int is_lr90, has_tda9820_tda9821;
	int tuner_type = UNSET, ttype;

	gpio_inout(0xffffff, 0);
	udelay(8);  /* without this we would see the 0x1800 mask */
	gpio = gpio_read();
	/* FIXME: must restore OUR_EN ??? */

	/* all cards provide GPIO info, some have an additional eeprom
	 * LR50: GPIO coding can be found lower right CP1 .. CP9
	 *       CP9=GPIO23 .. CP1=GPIO15; when OPEN, the corresponding GPIO reads 1.
	 *       GPIO14-12: n.c.
	 * LR90: GP9=GPIO23 .. GP1=GPIO15 (right above the bt878)

	 * lowest 3 bytes are remote control codes (no handshake needed)
	 * xxxFFF: No remote control chip soldered
	 * xxxF00(LR26/LR50), xxxFE0(LR90): Remote control chip (LVA001 or CF45) soldered
	 * Note: Some bits are Audio_Mask !
	 */
	ttype = (gpio & 0x0f0000) >> 16;
	switch (ttype) {
	case 0x0:
		tuner_type = 2;  /* NTSC, e.g. TPI8NSR11P */
		break;
	case 0x2:
		tuner_type = 39; /* LG NTSC (newer TAPC series) TAPC-H701P */
		break;
	case 0x4:
		tuner_type = 5;  /* Philips PAL TPI8PSB02P, TPI8PSB12P, TPI8PSB12D or FI1216, FM1216 */
		break;
	case 0x6:
		tuner_type = 37; /* LG PAL (newer TAPC series) TAPC-G702P */
		break;
	case 0xC:
		tuner_type = 3;  /* Philips SECAM(+PAL) FQ1216ME or FI1216MF */
		break;
	default:
		pr_info("%d: FlyVideo_gpio: unknown tuner type\n", btv->c.nr);
		break;
	}

	has_remote          =   gpio & 0x800000;
	has_radio	    =   gpio & 0x400000;
	/*   unknown                   0x200000;
	 *   unknown2                  0x100000; */
	is_capture_only     = !(gpio & 0x008000); /* GPIO15 */
	has_tda9820_tda9821 = !(gpio & 0x004000);
	is_lr90             = !(gpio & 0x002000); /* else LR26/LR50 (LR38/LR51 f. capture only) */
	/*
	 * gpio & 0x001000    output bit for audio routing */

	if (is_capture_only)
		tuner_type = TUNER_ABSENT; /* No tuner present */

	pr_info("%d: FlyVideo Radio=%s RemoteControl=%s Tuner=%d gpio=0x%06x\n",
		btv->c.nr, has_radio ? "yes" : "no",
		has_remote ? "yes" : "no", tuner_type, gpio);
	pr_info("%d: FlyVideo  LR90=%s tda9821/tda9820=%s capture_only=%s\n",
		btv->c.nr, is_lr90 ? "yes" : "no",
		has_tda9820_tda9821 ? "yes" : "no",
		is_capture_only ? "yes" : "no");

	if (tuner_type != UNSET) /* only set if known tuner autodetected, else let insmod option through */
		btv->tuner_type = tuner_type;
	btv->has_radio = has_radio;

	/* LR90 Audio Routing is done by 2 hef4052, so Audio_Mask has 4 bits: 0x001c80
	 * LR26/LR50 only has 1 hef4052, Audio_Mask 0x000c00
	 * Audio options: from tuner, from tda9821/tda9821(mono,stereo,sap), from tda9874, ext., mute */
	if (has_tda9820_tda9821)
		btv->audio_mode_gpio = lt9415_audio;
	/* todo: if(has_tda9874) btv->audio_mode_gpio = fv2000s_audio; */
}