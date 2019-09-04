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
typedef  int u32 ;
struct v4l2_tuner {int capability; scalar_t__ audmode; int /*<<< orphan*/  rxsubchans; } ;
struct cx88_core {int astat; int tvaudio; int /*<<< orphan*/  use_nicam; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CTL ; 
 int /*<<< orphan*/  AUD_STATUS ; 
 int /*<<< orphan*/  UNSET ; 
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_SAP ; 
 int V4L2_TUNER_CAP_STEREO ; 
 scalar_t__ V4L2_TUNER_MODE_LANG2 ; 
 void* V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_MODE_SAP ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
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
 int /*<<< orphan*/ * aud_ctl_names ; 
 int /*<<< orphan*/  cx88_dsp_detect_stereo_sap (struct cx88_core*) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,char const* const,char const* const,int /*<<< orphan*/ ) ; 

void cx88_get_stereo(struct cx88_core *core, struct v4l2_tuner *t)
{
	static const char * const m[] = { "stereo", "dual mono",
					  "mono",   "sap" };
	static const char * const p[] = { "no pilot", "pilot c1",
					  "pilot c2", "?" };
	u32 reg, mode, pilot;

	reg = cx_read(AUD_STATUS);
	mode = reg & 0x03;
	pilot = (reg >> 2) & 0x03;

	if (core->astat != reg)
		dprintk("AUD_STATUS: 0x%x [%s/%s] ctl=%s\n",
			reg, m[mode], p[pilot],
			aud_ctl_names[cx_read(AUD_CTL) & 63]);
	core->astat = reg;

	t->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_SAP |
	    V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	t->rxsubchans = UNSET;
	t->audmode = V4L2_TUNER_MODE_MONO;

	switch (mode) {
	case 0:
		t->audmode = V4L2_TUNER_MODE_STEREO;
		break;
	case 1:
		t->audmode = V4L2_TUNER_MODE_LANG2;
		break;
	case 2:
		t->audmode = V4L2_TUNER_MODE_MONO;
		break;
	case 3:
		t->audmode = V4L2_TUNER_MODE_SAP;
		break;
	}

	switch (core->tvaudio) {
	case WW_BTSC:
	case WW_BG:
	case WW_DK:
	case WW_M:
	case WW_EIAJ:
		if (!core->use_nicam) {
			t->rxsubchans = cx88_dsp_detect_stereo_sap(core);
			break;
		}
		break;
	case WW_NONE:
	case WW_I:
	case WW_L:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
		/* nothing */
		break;
	}

	/* If software stereo detection is not supported... */
	if (t->rxsubchans == UNSET) {
		t->rxsubchans = V4L2_TUNER_SUB_MONO;
		/*
		 * If the hardware itself detected stereo, also return
		 * stereo as an available subchannel
		 */
		if (t->audmode == V4L2_TUNER_MODE_STEREO)
			t->rxsubchans |= V4L2_TUNER_SUB_STEREO;
	}
}