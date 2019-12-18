#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_fract {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_4__ {struct v4l2_fract timeperframe; } ;
struct TYPE_5__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {TYPE_2__ parm; } ;
struct solo_enc_dev {int /*<<< orphan*/  interval; int /*<<< orphan*/  vidq; TYPE_3__* solo_dev; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fps; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  calc_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int solo_g_parm (struct file*,void*,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  solo_update_mode (struct solo_enc_dev*) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 struct solo_enc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_s_parm(struct file *file, void *priv,
		       struct v4l2_streamparm *sp)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);
	struct v4l2_fract *t = &sp->parm.capture.timeperframe;
	u8 fps = solo_enc->solo_dev->fps;

	if (vb2_is_streaming(&solo_enc->vidq))
		return -EBUSY;

	solo_enc->interval = calc_interval(fps, t->numerator, t->denominator);
	solo_update_mode(solo_enc);
	return solo_g_parm(file, priv, sp);
}