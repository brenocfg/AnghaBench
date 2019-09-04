#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {int gain1; int gain2; int gain4; int gain8; } ;
struct TYPE_6__ {int gain1; int gain2; int gain4; int gain8; } ;
struct TYPE_9__ {int coarseExpLo; int coarseExpHi; int expMode; int gain; int redComp; int green1Comp; int green2Comp; int blueComp; int compMode; int gainMode; } ;
struct TYPE_8__ {int coarseJump; int flickerMode; int disabled; } ;
struct TYPE_10__ {TYPE_2__ vlOffset; TYPE_1__ apcor; TYPE_4__ exposure; TYPE_3__ flickerControl; } ;
struct sd {TYPE_5__ params; int /*<<< orphan*/  exposure_status; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int COMP_BLUE ; 
 int COMP_GREEN1 ; 
 int COMP_GREEN2 ; 
 int COMP_RED ; 
 int /*<<< orphan*/  EXPOSURE_NORMAL ; 
 scalar_t__ FIRMWARE_VERSION (int,int) ; 
 int MAX_EXP ; 
 int MAX_EXP_102 ; 
 int ROUND_UP_EXP_FOR_FLICKER ; 
 int command_setapcor (struct gspca_dev*) ; 
 int command_setexposure (struct gspca_dev*) ; 
 int command_setflickerctrl (struct gspca_dev*) ; 
 int command_setvloffset (struct gspca_dev*) ; 

__attribute__((used)) static int set_flicker(struct gspca_dev *gspca_dev, int on, int apply)
{
	/* Everything in here is from the Windows driver */
/* define for compgain calculation */
#if 0
#define COMPGAIN(base, curexp, newexp) \
    (u8) ((((float) base - 128.0) * ((float) curexp / (float) newexp)) + 128.5)
#define EXP_FROM_COMP(basecomp, curcomp, curexp) \
    (u16)((float)curexp * (float)(u8)(curcomp + 128) / \
    (float)(u8)(basecomp - 128))
#else
  /* equivalent functions without floating point math */
#define COMPGAIN(base, curexp, newexp) \
    (u8)(128 + (((u32)(2*(base-128)*curexp + newexp)) / (2 * newexp)))
#define EXP_FROM_COMP(basecomp, curcomp, curexp) \
    (u16)(((u32)(curexp * (u8)(curcomp + 128)) / (u8)(basecomp - 128)))
#endif

	struct sd *sd = (struct sd *) gspca_dev;
	int currentexp = sd->params.exposure.coarseExpLo +
			 sd->params.exposure.coarseExpHi * 256;
	int ret, startexp;

	if (on) {
		int cj = sd->params.flickerControl.coarseJump;
		sd->params.flickerControl.flickerMode = 1;
		sd->params.flickerControl.disabled = 0;
		if (sd->params.exposure.expMode != 2) {
			sd->params.exposure.expMode = 2;
			sd->exposure_status = EXPOSURE_NORMAL;
		}
		currentexp = currentexp << sd->params.exposure.gain;
		sd->params.exposure.gain = 0;
		/* round down current exposure to nearest value */
		startexp = (currentexp + ROUND_UP_EXP_FOR_FLICKER) / cj;
		if (startexp < 1)
			startexp = 1;
		startexp = (startexp * cj) - 1;
		if (FIRMWARE_VERSION(1, 2))
			while (startexp > MAX_EXP_102)
				startexp -= cj;
		else
			while (startexp > MAX_EXP)
				startexp -= cj;
		sd->params.exposure.coarseExpLo = startexp & 0xff;
		sd->params.exposure.coarseExpHi = startexp >> 8;
		if (currentexp > startexp) {
			if (currentexp > (2 * startexp))
				currentexp = 2 * startexp;
			sd->params.exposure.redComp =
				COMPGAIN(COMP_RED, currentexp, startexp);
			sd->params.exposure.green1Comp =
				COMPGAIN(COMP_GREEN1, currentexp, startexp);
			sd->params.exposure.green2Comp =
				COMPGAIN(COMP_GREEN2, currentexp, startexp);
			sd->params.exposure.blueComp =
				COMPGAIN(COMP_BLUE, currentexp, startexp);
		} else {
			sd->params.exposure.redComp = COMP_RED;
			sd->params.exposure.green1Comp = COMP_GREEN1;
			sd->params.exposure.green2Comp = COMP_GREEN2;
			sd->params.exposure.blueComp = COMP_BLUE;
		}
		if (FIRMWARE_VERSION(1, 2))
			sd->params.exposure.compMode = 0;
		else
			sd->params.exposure.compMode = 1;

		sd->params.apcor.gain1 = 0x18;
		sd->params.apcor.gain2 = 0x18;
		sd->params.apcor.gain4 = 0x16;
		sd->params.apcor.gain8 = 0x14;
	} else {
		sd->params.flickerControl.flickerMode = 0;
		sd->params.flickerControl.disabled = 1;
		/* Average equivalent coarse for each comp channel */
		startexp = EXP_FROM_COMP(COMP_RED,
				sd->params.exposure.redComp, currentexp);
		startexp += EXP_FROM_COMP(COMP_GREEN1,
				sd->params.exposure.green1Comp, currentexp);
		startexp += EXP_FROM_COMP(COMP_GREEN2,
				sd->params.exposure.green2Comp, currentexp);
		startexp += EXP_FROM_COMP(COMP_BLUE,
				sd->params.exposure.blueComp, currentexp);
		startexp = startexp >> 2;
		while (startexp > MAX_EXP && sd->params.exposure.gain <
		       sd->params.exposure.gainMode - 1) {
			startexp = startexp >> 1;
			++sd->params.exposure.gain;
		}
		if (FIRMWARE_VERSION(1, 2) && startexp > MAX_EXP_102)
			startexp = MAX_EXP_102;
		if (startexp > MAX_EXP)
			startexp = MAX_EXP;
		sd->params.exposure.coarseExpLo = startexp & 0xff;
		sd->params.exposure.coarseExpHi = startexp >> 8;
		sd->params.exposure.redComp = COMP_RED;
		sd->params.exposure.green1Comp = COMP_GREEN1;
		sd->params.exposure.green2Comp = COMP_GREEN2;
		sd->params.exposure.blueComp = COMP_BLUE;
		sd->params.exposure.compMode = 1;
		sd->params.apcor.gain1 = 0x18;
		sd->params.apcor.gain2 = 0x16;
		sd->params.apcor.gain4 = 0x24;
		sd->params.apcor.gain8 = 0x34;
	}
	sd->params.vlOffset.gain1 = 20;
	sd->params.vlOffset.gain2 = 24;
	sd->params.vlOffset.gain4 = 26;
	sd->params.vlOffset.gain8 = 26;

	if (apply) {
		ret = command_setexposure(gspca_dev);
		if (ret)
			return ret;

		ret = command_setapcor(gspca_dev);
		if (ret)
			return ret;

		ret = command_setvloffset(gspca_dev);
		if (ret)
			return ret;

		ret = command_setflickerctrl(gspca_dev);
		if (ret)
			return ret;
	}

	return 0;
#undef EXP_FROM_COMP
#undef COMPGAIN
}