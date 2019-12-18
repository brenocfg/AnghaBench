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
typedef  int /*<<< orphan*/  u16 ;
struct si4713_device {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int ATTACK_TIME_UNIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_ATTACK_TIME ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_ENABLE ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_GAIN ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_RELEASE_TIME ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_THRESHOLD ; 
 int /*<<< orphan*/  SI4713_TX_AUDIO_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_COMPONENT_ENABLE ; 
 int /*<<< orphan*/  SI4713_TX_LIMITER_RELEASE_TIME ; 
 int /*<<< orphan*/  SI4713_TX_PILOT_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_PILOT_FREQUENCY ; 
 int /*<<< orphan*/  SI4713_TX_PREEMPHASIS ; 
 int /*<<< orphan*/  SI4713_TX_RDS_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_RDS_PI ; 
 int /*<<< orphan*/  SI4713_TX_RDS_PS_MISC ; 
#define  V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME 149 
#define  V4L2_CID_AUDIO_COMPRESSION_ENABLED 148 
#define  V4L2_CID_AUDIO_COMPRESSION_GAIN 147 
#define  V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME 146 
#define  V4L2_CID_AUDIO_COMPRESSION_THRESHOLD 145 
#define  V4L2_CID_AUDIO_LIMITER_DEVIATION 144 
#define  V4L2_CID_AUDIO_LIMITER_ENABLED 143 
#define  V4L2_CID_AUDIO_LIMITER_RELEASE_TIME 142 
#define  V4L2_CID_PILOT_TONE_DEVIATION 141 
#define  V4L2_CID_PILOT_TONE_ENABLED 140 
#define  V4L2_CID_PILOT_TONE_FREQUENCY 139 
#define  V4L2_CID_RDS_TX_ARTIFICIAL_HEAD 138 
#define  V4L2_CID_RDS_TX_COMPRESSED 137 
#define  V4L2_CID_RDS_TX_DEVIATION 136 
#define  V4L2_CID_RDS_TX_DYNAMIC_PTY 135 
#define  V4L2_CID_RDS_TX_MONO_STEREO 134 
#define  V4L2_CID_RDS_TX_MUSIC_SPEECH 133 
#define  V4L2_CID_RDS_TX_PI 132 
#define  V4L2_CID_RDS_TX_PTY 131 
#define  V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT 130 
#define  V4L2_CID_RDS_TX_TRAFFIC_PROGRAM 129 
#define  V4L2_CID_TUNE_PREEMPHASIS 128 
 unsigned long* acomp_rtimes ; 
 unsigned long* limiter_times ; 
 unsigned long* preemphasis_values ; 

__attribute__((used)) static int si4713_choose_econtrol_action(struct si4713_device *sdev, u32 id,
		s32 *bit, s32 *mask, u16 *property, int *mul,
		unsigned long **table, int *size)
{
	s32 rval = 0;

	switch (id) {
	/* FM_TX class controls */
	case V4L2_CID_RDS_TX_PI:
		*property = SI4713_TX_RDS_PI;
		*mul = 1;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_THRESHOLD:
		*property = SI4713_TX_ACOMP_THRESHOLD;
		*mul = 1;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_GAIN:
		*property = SI4713_TX_ACOMP_GAIN;
		*mul = 1;
		break;
	case V4L2_CID_PILOT_TONE_FREQUENCY:
		*property = SI4713_TX_PILOT_FREQUENCY;
		*mul = 1;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME:
		*property = SI4713_TX_ACOMP_ATTACK_TIME;
		*mul = ATTACK_TIME_UNIT;
		break;
	case V4L2_CID_PILOT_TONE_DEVIATION:
		*property = SI4713_TX_PILOT_DEVIATION;
		*mul = 10;
		break;
	case V4L2_CID_AUDIO_LIMITER_DEVIATION:
		*property = SI4713_TX_AUDIO_DEVIATION;
		*mul = 10;
		break;
	case V4L2_CID_RDS_TX_DEVIATION:
		*property = SI4713_TX_RDS_DEVIATION;
		*mul = 1;
		break;

	case V4L2_CID_RDS_TX_PTY:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 5;
		*mask = 0x1F << 5;
		break;
	case V4L2_CID_RDS_TX_DYNAMIC_PTY:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 15;
		*mask = 1 << 15;
		break;
	case V4L2_CID_RDS_TX_COMPRESSED:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 14;
		*mask = 1 << 14;
		break;
	case V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 13;
		*mask = 1 << 13;
		break;
	case V4L2_CID_RDS_TX_MONO_STEREO:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 12;
		*mask = 1 << 12;
		break;
	case V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 10;
		*mask = 1 << 10;
		break;
	case V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 4;
		*mask = 1 << 4;
		break;
	case V4L2_CID_RDS_TX_MUSIC_SPEECH:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 3;
		*mask = 1 << 3;
		break;
	case V4L2_CID_AUDIO_LIMITER_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 1;
		*mask = 1 << 1;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		break;
	case V4L2_CID_PILOT_TONE_ENABLED:
		*property = SI4713_TX_COMPONENT_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		break;

	case V4L2_CID_AUDIO_LIMITER_RELEASE_TIME:
		*property = SI4713_TX_LIMITER_RELEASE_TIME;
		*table = limiter_times;
		*size = ARRAY_SIZE(limiter_times);
		break;
	case V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME:
		*property = SI4713_TX_ACOMP_RELEASE_TIME;
		*table = acomp_rtimes;
		*size = ARRAY_SIZE(acomp_rtimes);
		break;
	case V4L2_CID_TUNE_PREEMPHASIS:
		*property = SI4713_TX_PREEMPHASIS;
		*table = preemphasis_values;
		*size = ARRAY_SIZE(preemphasis_values);
		break;

	default:
		rval = -EINVAL;
		break;
	}

	return rval;
}