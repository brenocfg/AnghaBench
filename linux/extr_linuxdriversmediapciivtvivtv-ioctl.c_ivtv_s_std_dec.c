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
typedef  int v4l2_std_id ;
struct TYPE_2__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct yuv_playback_info {int osd_full_w; int osd_full_h; TYPE_1__ main_rect; } ;
struct ivtv {int std_out; int is_out_60hz; int is_out_50hz; int /*<<< orphan*/  osd_info; TYPE_1__ main_rect; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  vsync_waitq; struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_SET_STANDARD ; 
 int /*<<< orphan*/  CX2341X_OSD_SET_FRAMEBUFFER_WINDOW ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_REG_DEC_LINE_FIELD ; 
 int /*<<< orphan*/  IVTV_WARN (char*) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_std_output ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  wait ; 

void ivtv_s_std_dec(struct ivtv *itv, v4l2_std_id std)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	DEFINE_WAIT(wait);
	int f;

	/* set display standard */
	itv->std_out = std;
	itv->is_out_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	itv->is_out_50hz = !itv->is_out_60hz;
	ivtv_call_all(itv, video, s_std_output, itv->std_out);

	/*
	 * The next firmware call is time sensitive. Time it to
	 * avoid risk of a hard lock, by trying to ensure the call
	 * happens within the first 100 lines of the top field.
	 * Make 4 attempts to sync to the decoder before giving up.
	 */
	mutex_unlock(&itv->serialize_lock);
	for (f = 0; f < 4; f++) {
		prepare_to_wait(&itv->vsync_waitq, &wait,
				TASK_UNINTERRUPTIBLE);
		if ((read_reg(IVTV_REG_DEC_LINE_FIELD) >> 16) < 100)
			break;
		schedule_timeout(msecs_to_jiffies(25));
	}
	finish_wait(&itv->vsync_waitq, &wait);
	mutex_lock(&itv->serialize_lock);

	if (f == 4)
		IVTV_WARN("Mode change failed to sync to decoder\n");

	ivtv_vapi(itv, CX2341X_DEC_SET_STANDARD, 1, itv->is_out_50hz);
	itv->main_rect.left = 0;
	itv->main_rect.top = 0;
	itv->main_rect.width = 720;
	itv->main_rect.height = itv->is_out_50hz ? 576 : 480;
	ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
		720, itv->main_rect.height, 0, 0);
	yi->main_rect = itv->main_rect;
	if (!itv->osd_info) {
		yi->osd_full_w = 720;
		yi->osd_full_h = itv->is_out_50hz ? 576 : 480;
	}
}