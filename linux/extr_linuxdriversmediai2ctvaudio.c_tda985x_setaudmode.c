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
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; } ;

/* Variables and functions */
 int TDA985x_C6 ; 
 int TDA985x_MONO ; 
 int TDA985x_MONOSAP ; 
 int TDA985x_SAP ; 
 int TDA985x_STEREO ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_MONO 130 
#define  V4L2_TUNER_MODE_SAP 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int,int) ; 

__attribute__((used)) static void tda985x_setaudmode(struct CHIPSTATE *chip, int mode)
{
	int update = 1;
	int c6 = chip->shadow.bytes[TDA985x_C6+1] & 0x3f;

	switch (mode) {
	case V4L2_TUNER_MODE_MONO:
		c6 |= TDA985x_MONO;
		break;
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1:
		c6 |= TDA985x_STEREO;
		break;
	case V4L2_TUNER_MODE_SAP:
		c6 |= TDA985x_SAP;
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		c6 |= TDA985x_MONOSAP;
		break;
	default:
		update = 0;
	}
	if (update)
		chip_write(chip,TDA985x_C6,c6);
}