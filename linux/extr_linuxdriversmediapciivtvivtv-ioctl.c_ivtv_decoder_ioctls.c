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
struct ivtv_stream {int dummy; } ;
struct ivtv_open_id {size_t type; int yuv_frames; struct ivtv* itv; } ;
struct ivtv_dma_frame {int /*<<< orphan*/ * y_source; int /*<<< orphan*/  type; } ;
struct ivtv {int v4l2_cap; int /*<<< orphan*/  output_mode; struct ivtv_stream* streams; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_IOCTL (char*) ; 
#define  IVTV_IOC_DMA_FRAME 129 
#define  IVTV_IOC_PASSTHROUGH_MODE 128 
 int /*<<< orphan*/  OUT_UDMA_YUV ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int ivtv_passthrough_mode (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_set_output_mode (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_start_decoding (struct ivtv_open_id*,size_t) ; 
 int ivtv_yuv_prep_frame (struct ivtv*,struct ivtv_dma_frame*) ; 

__attribute__((used)) static int ivtv_decoder_ioctls(struct file *filp, unsigned int cmd, void *arg)
{
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
#ifdef CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	int nonblocking = filp->f_flags & O_NONBLOCK;
	unsigned long iarg = (unsigned long)arg;
#endif

	switch (cmd) {
	case IVTV_IOC_DMA_FRAME: {
		struct ivtv_dma_frame *args = arg;

		IVTV_DEBUG_IOCTL("IVTV_IOC_DMA_FRAME\n");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		if (args->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		if (itv->output_mode == OUT_UDMA_YUV && args->y_source == NULL)
			return 0;
		if (ivtv_start_decoding(id, id->type)) {
			return -EBUSY;
		}
		if (ivtv_set_output_mode(itv, OUT_UDMA_YUV) != OUT_UDMA_YUV) {
			ivtv_release_stream(s);
			return -EBUSY;
		}
		/* Mark that this file handle started the UDMA_YUV mode */
		id->yuv_frames = 1;
		if (args->y_source == NULL)
			return 0;
		return ivtv_yuv_prep_frame(itv, args);
	}

	case IVTV_IOC_PASSTHROUGH_MODE:
		IVTV_DEBUG_IOCTL("IVTV_IOC_PASSTHROUGH_MODE\n");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		return ivtv_passthrough_mode(itv, *(int *)arg != 0);
#ifdef CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	case VIDEO_GET_PTS: {
		s64 *pts = arg;
		s64 frame;

		warn_deprecated_ioctl("VIDEO_GET_PTS");
		if (s->type < IVTV_DEC_STREAM_TYPE_MPG) {
			*pts = s->dma_pts;
			break;
		}
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		return ivtv_g_pts_frame(itv, pts, &frame);
	}

	case VIDEO_GET_FRAME_COUNT: {
		s64 *frame = arg;
		s64 pts;

		warn_deprecated_ioctl("VIDEO_GET_FRAME_COUNT");
		if (s->type < IVTV_DEC_STREAM_TYPE_MPG) {
			*frame = 0;
			break;
		}
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		return ivtv_g_pts_frame(itv, &pts, frame);
	}

	case VIDEO_PLAY: {
		struct v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_PLAY");
		memset(&dc, 0, sizeof(dc));
		dc.cmd = V4L2_DEC_CMD_START;
		return ivtv_video_command(itv, id, &dc, 0);
	}

	case VIDEO_STOP: {
		struct v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_STOP");
		memset(&dc, 0, sizeof(dc));
		dc.cmd = V4L2_DEC_CMD_STOP;
		dc.flags = V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY;
		return ivtv_video_command(itv, id, &dc, 0);
	}

	case VIDEO_FREEZE: {
		struct v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_FREEZE");
		memset(&dc, 0, sizeof(dc));
		dc.cmd = V4L2_DEC_CMD_PAUSE;
		return ivtv_video_command(itv, id, &dc, 0);
	}

	case VIDEO_CONTINUE: {
		struct v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_CONTINUE");
		memset(&dc, 0, sizeof(dc));
		dc.cmd = V4L2_DEC_CMD_RESUME;
		return ivtv_video_command(itv, id, &dc, 0);
	}

	case VIDEO_COMMAND:
	case VIDEO_TRY_COMMAND: {
		/* Note: struct v4l2_decoder_cmd has the same layout as
		   struct video_command */
		struct v4l2_decoder_cmd *dc = arg;
		int try = (cmd == VIDEO_TRY_COMMAND);

		if (try)
			warn_deprecated_ioctl("VIDEO_TRY_COMMAND");
		else
			warn_deprecated_ioctl("VIDEO_COMMAND");
		return ivtv_video_command(itv, id, dc, try);
	}

	case VIDEO_GET_EVENT: {
		struct video_event *ev = arg;
		DEFINE_WAIT(wait);

		warn_deprecated_ioctl("VIDEO_GET_EVENT");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		memset(ev, 0, sizeof(*ev));
		set_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);

		while (1) {
			if (test_and_clear_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags))
				ev->type = VIDEO_EVENT_DECODER_STOPPED;
			else if (test_and_clear_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags)) {
				ev->type = VIDEO_EVENT_VSYNC;
				ev->u.vsync_field = test_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags) ?
					VIDEO_VSYNC_FIELD_ODD : VIDEO_VSYNC_FIELD_EVEN;
				if (itv->output_mode == OUT_UDMA_YUV &&
					(itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) ==
								IVTV_YUV_MODE_PROGRESSIVE) {
					ev->u.vsync_field = VIDEO_VSYNC_FIELD_PROGRESSIVE;
				}
			}
			if (ev->type)
				return 0;
			if (nonblocking)
				return -EAGAIN;
			/* Wait for event. Note that serialize_lock is locked,
			   so to allow other processes to access the driver while
			   we are waiting unlock first and later lock again. */
			mutex_unlock(&itv->serialize_lock);
			prepare_to_wait(&itv->event_waitq, &wait, TASK_INTERRUPTIBLE);
			if (!test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags) &&
			    !test_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags))
				schedule();
			finish_wait(&itv->event_waitq, &wait);
			mutex_lock(&itv->serialize_lock);
			if (signal_pending(current)) {
				/* return if a signal was received */
				IVTV_DEBUG_INFO("User stopped wait for event\n");
				return -EINTR;
			}
		}
		break;
	}

	case VIDEO_SELECT_SOURCE:
		warn_deprecated_ioctl("VIDEO_SELECT_SOURCE");
		if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			return -EINVAL;
		return ivtv_passthrough_mode(itv, iarg == VIDEO_SOURCE_DEMUX);

	case AUDIO_SET_MUTE:
		warn_deprecated_ioctl("AUDIO_SET_MUTE");
		itv->speed_mute_audio = iarg;
		return 0;

	case AUDIO_CHANNEL_SELECT:
		warn_deprecated_ioctl("AUDIO_CHANNEL_SELECT");
		if (iarg > AUDIO_STEREO_SWAPPED)
			return -EINVAL;
		return v4l2_ctrl_s_ctrl(itv->ctrl_audio_playback, iarg + 1);

	case AUDIO_BILINGUAL_CHANNEL_SELECT:
		warn_deprecated_ioctl("AUDIO_BILINGUAL_CHANNEL_SELECT");
		if (iarg > AUDIO_STEREO_SWAPPED)
			return -EINVAL;
		return v4l2_ctrl_s_ctrl(itv->ctrl_audio_multilingual_playback, iarg + 1);
#endif
	default:
		return -EINVAL;
	}
	return 0;
}