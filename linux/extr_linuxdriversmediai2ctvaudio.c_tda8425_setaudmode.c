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
 int TDA8425_S1 ; 
 int TDA8425_S1_ML_SOUND_A ; 
 int TDA8425_S1_ML_SOUND_B ; 
 int TDA8425_S1_ML_STEREO ; 
 int TDA8425_S1_STEREO_LINEAR ; 
 int TDA8425_S1_STEREO_MONO ; 
 int TDA8425_S1_STEREO_PSEUDO ; 
 int TDA8425_S1_STEREO_SPATIAL ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int,int) ; 

__attribute__((used)) static void tda8425_setaudmode(struct CHIPSTATE *chip, int mode)
{
	int s1 = chip->shadow.bytes[TDA8425_S1+1] & 0xe1;

	switch (mode) {
	case V4L2_TUNER_MODE_LANG1:
		s1 |= TDA8425_S1_ML_SOUND_A;
		s1 |= TDA8425_S1_STEREO_PSEUDO;
		break;
	case V4L2_TUNER_MODE_LANG2:
		s1 |= TDA8425_S1_ML_SOUND_B;
		s1 |= TDA8425_S1_STEREO_PSEUDO;
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_LINEAR;
		break;
	case V4L2_TUNER_MODE_MONO:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_MONO;
		break;
	case V4L2_TUNER_MODE_STEREO:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_SPATIAL;
		break;
	default:
		return;
	}
	chip_write(chip,TDA8425_S1,s1);
}