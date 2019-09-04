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
struct TYPE_2__ {int i2sinputcntl; } ;
struct cx88_core {int tvaudio; int use_nicam; TYPE_1__ board; int /*<<< orphan*/  audiomode_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_I2SCNTL ; 
 int /*<<< orphan*/  AUD_I2SINPUTCNTL ; 
 int /*<<< orphan*/  EN_A2_FORCE_MONO1 ; 
 int /*<<< orphan*/  EN_BTSC_AUTO_STEREO ; 
 int /*<<< orphan*/  EN_I2SIN_ENABLE ; 
 int /*<<< orphan*/  EN_NICAM_AUTO_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_MONO ; 
#define  WW_BG 138 
#define  WW_BTSC 137 
#define  WW_DK 136 
#define  WW_EIAJ 135 
#define  WW_FM 134 
#define  WW_I 133 
#define  WW_I2SADC 132 
#define  WW_I2SPT 131 
#define  WW_L 130 
#define  WW_M 129 
#define  WW_NONE 128 
 int /*<<< orphan*/  cx88_detect_nicam (struct cx88_core*) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  radio_deemphasis ; 
 int /*<<< orphan*/  set_audio_finish (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_standard_A2 (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_standard_BTSC (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_standard_EIAJ (struct cx88_core*) ; 
 int /*<<< orphan*/  set_audio_standard_FM (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_standard_NICAM (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_audio_start (struct cx88_core*,int) ; 

void cx88_set_tvaudio(struct cx88_core *core)
{
	switch (core->tvaudio) {
	case WW_BTSC:
		set_audio_standard_BTSC(core, 0, EN_BTSC_AUTO_STEREO);
		break;
	case WW_BG:
	case WW_DK:
	case WW_M:
	case WW_I:
	case WW_L:
		/* prepare all dsp registers */
		set_audio_standard_A2(core, EN_A2_FORCE_MONO1);

		/*
		 * set nicam mode - otherwise
		 * AUD_NICAM_STATUS2 contains wrong values
		 */
		set_audio_standard_NICAM(core, EN_NICAM_AUTO_STEREO);
		if (cx88_detect_nicam(core) == 0) {
			/* fall back to fm / am mono */
			set_audio_standard_A2(core, EN_A2_FORCE_MONO1);
			core->audiomode_current = V4L2_TUNER_MODE_MONO;
			core->use_nicam = 0;
		} else {
			core->use_nicam = 1;
		}
		break;
	case WW_EIAJ:
		set_audio_standard_EIAJ(core);
		break;
	case WW_FM:
		set_audio_standard_FM(core, radio_deemphasis);
		break;
	case WW_I2SADC:
		set_audio_start(core, 0x01);
		/*
		 * Slave/Philips/Autobaud
		 * NB on Nova-S bit1 NPhilipsSony appears to be inverted:
		 *	0= Sony, 1=Philips
		 */
		cx_write(AUD_I2SINPUTCNTL, core->board.i2sinputcntl);
		/* Switch to "I2S ADC mode" */
		cx_write(AUD_I2SCNTL, 0x1);
		set_audio_finish(core, EN_I2SIN_ENABLE);
		break;
	case WW_NONE:
	case WW_I2SPT:
		pr_info("unknown tv audio mode [%d]\n", core->tvaudio);
		break;
	}
}