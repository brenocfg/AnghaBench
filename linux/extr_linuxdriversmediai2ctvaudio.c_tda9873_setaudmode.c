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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int TDA9873_INP_MASK ; 
 int TDA9873_INTERNAL ; 
 int TDA9873_SW ; 
 int TDA9873_TR_DUALA ; 
 int TDA9873_TR_DUALAB ; 
 int TDA9873_TR_DUALB ; 
 int TDA9873_TR_MASK ; 
 int TDA9873_TR_MONO ; 
 int TDA9873_TR_STEREO ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static void tda9873_setaudmode(struct CHIPSTATE *chip, int mode)
{
	struct v4l2_subdev *sd = &chip->sd;
	int sw_data  = chip->shadow.bytes[TDA9873_SW+1] & ~ TDA9873_TR_MASK;
	/*	int adj_data = chip->shadow.bytes[TDA9873_AD+1] ; */

	if ((sw_data & TDA9873_INP_MASK) != TDA9873_INTERNAL) {
		v4l2_dbg(1, debug, sd,
			 "tda9873_setaudmode(): external input\n");
		return;
	}

	v4l2_dbg(1, debug, sd,
		 "tda9873_setaudmode(): chip->shadow.bytes[%d] = %d\n",
		 TDA9873_SW+1, chip->shadow.bytes[TDA9873_SW+1]);
	v4l2_dbg(1, debug, sd, "tda9873_setaudmode(): sw_data  = %d\n",
		 sw_data);

	switch (mode) {
	case V4L2_TUNER_MODE_MONO:
		sw_data |= TDA9873_TR_MONO;
		break;
	case V4L2_TUNER_MODE_STEREO:
		sw_data |= TDA9873_TR_STEREO;
		break;
	case V4L2_TUNER_MODE_LANG1:
		sw_data |= TDA9873_TR_DUALA;
		break;
	case V4L2_TUNER_MODE_LANG2:
		sw_data |= TDA9873_TR_DUALB;
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		sw_data |= TDA9873_TR_DUALAB;
		break;
	default:
		return;
	}

	chip_write(chip, TDA9873_SW, sw_data);
	v4l2_dbg(1, debug, sd,
		"tda9873_setaudmode(): req. mode %d; chip_write: %d\n",
		mode, sw_data);
}