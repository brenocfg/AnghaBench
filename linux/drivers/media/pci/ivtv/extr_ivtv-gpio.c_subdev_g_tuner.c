#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct v4l2_tuner {int rxsubchans; } ;
struct v4l2_subdev {int dummy; } ;
struct ivtv {TYPE_2__* card; } ;
struct TYPE_3__ {int mask; } ;
struct TYPE_4__ {TYPE_1__ gpio_audio_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_GPIO_IN ; 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 struct ivtv* sd_to_ivtv (struct v4l2_subdev*) ; 

__attribute__((used)) static int subdev_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct ivtv *itv = sd_to_ivtv(sd);
	u16 mask;

	mask = itv->card->gpio_audio_detect.mask;
	if (mask == 0 || (read_reg(IVTV_REG_GPIO_IN) & mask))
		vt->rxsubchans = V4L2_TUNER_SUB_STEREO |
			V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	else
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	return 0;
}