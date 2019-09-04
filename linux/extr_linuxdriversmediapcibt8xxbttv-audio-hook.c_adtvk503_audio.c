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
struct v4l2_tuner {int audmode; int rxsubchans; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 

void adtvk503_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	unsigned int con = 0xffffff;

	/* btaor(0x1e0000, ~0x1e0000, BT848_GPIO_OUT_EN); */

	if (!set) {
		/* Not much to do here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		return;
	}

	/* btor(***, BT848_GPIO_OUT_EN); */
	switch (t->audmode) {
	case V4L2_TUNER_MODE_LANG1:
		con = 0x00000000;
		break;
	case V4L2_TUNER_MODE_LANG2:
		con = 0x00180000;
		break;
	case V4L2_TUNER_MODE_STEREO:
		con = 0x00000000;
		break;
	case V4L2_TUNER_MODE_MONO:
		con = 0x00060000;
		break;
	default:
		return;
	}

	gpio_bits(0x1e0000, con);
	if (bttv_gpio)
		bttv_gpio_tracking(btv, "adtvk503");
}