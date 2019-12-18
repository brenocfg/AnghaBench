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
#define  V4L2_TUNER_MODE_LANG1 130 
#define  V4L2_TUNER_MODE_LANG2 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 

void gvbctv3pci_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	unsigned int con;

	if (!set) {
		/* Not much to do here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		return;
	}

	gpio_inout(0x300, 0x300);
	switch (t->audmode) {
	case V4L2_TUNER_MODE_LANG1:
	default:
		con = 0x000;
		break;
	case V4L2_TUNER_MODE_LANG2:
		con = 0x300;
		break;
	case V4L2_TUNER_MODE_STEREO:
		con = 0x200;
		break;
	}
	gpio_bits(0x300, con);
}