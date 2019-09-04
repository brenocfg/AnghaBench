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
struct ivtv_stream {scalar_t__ type; int /*<<< orphan*/  s_flags; int /*<<< orphan*/ * fh; int /*<<< orphan*/  name; } ;
struct ivtv_open_id {size_t type; int /*<<< orphan*/  fh; struct ivtv* itv; } ;
struct TYPE_2__ {int /*<<< orphan*/  video_mute_yuv; int /*<<< orphan*/  video_mute; } ;
struct ivtv {int hw_flags; scalar_t__ output_mode; int /*<<< orphan*/  serialize_lock; struct ivtv_stream* streams; TYPE_1__ cxhdl; int /*<<< orphan*/  capturing; int /*<<< orphan*/  std; int /*<<< orphan*/  i_flags; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_MUTE_VIDEO ; 
 int /*<<< orphan*/  IVTV_DEBUG_FILE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IVTV_DEC_STREAM_TYPE_MPG ; 
 size_t IVTV_DEC_STREAM_TYPE_VOUT ; 
 size_t IVTV_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  IVTV_F_I_RADIO_USER ; 
 int /*<<< orphan*/  IVTV_F_S_APPL_IO ; 
 int IVTV_HW_SAA711X ; 
 scalar_t__ OUT_NONE ; 
 int /*<<< orphan*/  SAA7115_FREQ_32_11_MHZ ; 
 int V4L2_DEC_CMD_STOP_IMMEDIATELY ; 
 int V4L2_DEC_CMD_STOP_TO_BLACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ivtv_open_id* fh2id (struct v4l2_fh*) ; 
 int /*<<< orphan*/  ivtv_audio_set_io (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_disable_cc (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_mute (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_stop_capture (struct ivtv_open_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_stop_decoding (struct ivtv_open_id*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_unmute (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct ivtv_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_crystal_freq ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  video ; 

int ivtv_v4l2_close(struct file *filp)
{
	struct v4l2_fh *fh = filp->private_data;
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];

	IVTV_DEBUG_FILE("close %s\n", s->name);

	mutex_lock(&itv->serialize_lock);

	/* Stop radio */
	if (id->type == IVTV_ENC_STREAM_TYPE_RAD &&
			v4l2_fh_is_singular_file(filp)) {
		/* Closing radio device, return to TV mode */
		ivtv_mute(itv);
		/* Mark that the radio is no longer in use */
		clear_bit(IVTV_F_I_RADIO_USER, &itv->i_flags);
		/* Switch tuner to TV */
		ivtv_call_all(itv, video, s_std, itv->std);
		/* Select correct audio input (i.e. TV tuner or Line in) */
		ivtv_audio_set_io(itv);
		if (itv->hw_flags & IVTV_HW_SAA711X) {
			ivtv_call_hw(itv, IVTV_HW_SAA711X, video, s_crystal_freq,
					SAA7115_FREQ_32_11_MHZ, 0);
		}
		if (atomic_read(&itv->capturing) > 0) {
			/* Undo video mute */
			ivtv_vapi(itv, CX2341X_ENC_MUTE_VIDEO, 1,
					v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute) |
					(v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute_yuv) << 8));
		}
		/* Done! Unmute and continue. */
		ivtv_unmute(itv);
	}

	v4l2_fh_del(fh);
	v4l2_fh_exit(fh);

	/* Easy case first: this stream was never claimed by us */
	if (s->fh != &id->fh)
		goto close_done;

	/* 'Unclaim' this stream */

	if (s->type >= IVTV_DEC_STREAM_TYPE_MPG) {
		struct ivtv_stream *s_vout = &itv->streams[IVTV_DEC_STREAM_TYPE_VOUT];

		ivtv_stop_decoding(id, V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY, 0);

		/* If all output streams are closed, and if the user doesn't have
		   IVTV_DEC_STREAM_TYPE_VOUT open, then disable CC on TV-out. */
		if (itv->output_mode == OUT_NONE && !test_bit(IVTV_F_S_APPL_IO, &s_vout->s_flags)) {
			/* disable CC on TV-out */
			ivtv_disable_cc(itv);
		}
	} else {
		ivtv_stop_capture(id, 0);
	}
close_done:
	kfree(id);
	mutex_unlock(&itv->serialize_lock);
	return 0;
}