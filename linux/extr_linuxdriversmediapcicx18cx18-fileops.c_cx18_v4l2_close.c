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
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;
struct cx18_stream {scalar_t__ id; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; } ;
struct cx18_open_id {size_t type; scalar_t__ open_id; struct cx18* cx; } ;
struct TYPE_2__ {int /*<<< orphan*/  video_mute_yuv; int /*<<< orphan*/  video_mute; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; TYPE_1__ cxhdl; int /*<<< orphan*/  ana_capturing; int /*<<< orphan*/  std; int /*<<< orphan*/  i_flags; struct cx18_stream* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_SET_VIDEO_MUTE ; 
 int /*<<< orphan*/  CX18_DEBUG_IOCTL (char*,int /*<<< orphan*/ ) ; 
 size_t CX18_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_audio_set_io (struct cx18*) ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_mute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_stop_capture (struct cx18_open_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_unmute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct cx18_open_id* fh2id (struct v4l2_fh*) ; 
 int /*<<< orphan*/  kfree (struct cx18_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_std ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  video ; 

int cx18_v4l2_close(struct file *filp)
{
	struct v4l2_fh *fh = filp->private_data;
	struct cx18_open_id *id = fh2id(fh);
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];

	CX18_DEBUG_IOCTL("close() of %s\n", s->name);

	mutex_lock(&cx->serialize_lock);
	/* Stop radio */
	if (id->type == CX18_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) {
		/* Closing radio device, return to TV mode */
		cx18_mute(cx);
		/* Mark that the radio is no longer in use */
		clear_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
		/* Switch tuner to TV */
		cx18_call_all(cx, video, s_std, cx->std);
		/* Select correct audio input (i.e. TV tuner or Line in) */
		cx18_audio_set_io(cx);
		if (atomic_read(&cx->ana_capturing) > 0) {
			/* Undo video mute */
			cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handle,
			    (v4l2_ctrl_g_ctrl(cx->cxhdl.video_mute) |
			    (v4l2_ctrl_g_ctrl(cx->cxhdl.video_mute_yuv) << 8)));
		}
		/* Done! Unmute and continue. */
		cx18_unmute(cx);
	}

	v4l2_fh_del(fh);
	v4l2_fh_exit(fh);

	/* 'Unclaim' this stream */
	if (s->id == id->open_id)
		cx18_stop_capture(id, 0);
	kfree(id);
	mutex_unlock(&cx->serialize_lock);
	return 0;
}