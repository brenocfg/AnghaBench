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
struct TYPE_6__ {unsigned char vsync_field; } ;
struct video_event {int flags; int /*<<< orphan*/  type; TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct v4l2_decoder_cmd {int flags; int /*<<< orphan*/  type; TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct ivtv_stream {int /*<<< orphan*/  type; int /*<<< orphan*/  dma_pts; } ;
struct ivtv_open_id {size_t type; int yuv_frames; struct ivtv* itv; } ;
struct ivtv_dma_frame {int /*<<< orphan*/ * y_source; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int lace_mode; } ;
struct ivtv {int v4l2_cap; unsigned long speed_mute_audio; int /*<<< orphan*/  ctrl_audio_multilingual_playback; int /*<<< orphan*/  ctrl_audio_playback; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  event_waitq; int /*<<< orphan*/  i_flags; TYPE_1__ yuv_info; int /*<<< orphan*/  output_mode; struct ivtv_stream* streams; } ;
struct file {int f_flags; int /*<<< orphan*/  private_data; } ;
struct TYPE_5__ {unsigned char vsync_field; } ;
struct compat_video_event {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  dc ;

/* Variables and functions */
#define  AUDIO_BILINGUAL_CHANNEL_SELECT 143 
#define  AUDIO_CHANNEL_SELECT 142 
#define  AUDIO_SET_MUTE 141 
 unsigned long AUDIO_STEREO_SWAPPED ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_IOCTL (char*) ; 
 int /*<<< orphan*/  IVTV_DEC_STREAM_TYPE_MPG ; 
 int /*<<< orphan*/  IVTV_F_I_EV_DEC_STOPPED ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC_ENABLED ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC_FIELD ; 
#define  IVTV_IOC_DMA_FRAME 140 
#define  IVTV_IOC_PASSTHROUGH_MODE 139 
 int IVTV_YUV_MODE_MASK ; 
 int IVTV_YUV_MODE_PROGRESSIVE ; 
 int /*<<< orphan*/  OUT_UDMA_YUV ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_DEC_CMD_PAUSE ; 
 int /*<<< orphan*/  V4L2_DEC_CMD_RESUME ; 
 int /*<<< orphan*/  V4L2_DEC_CMD_START ; 
 int /*<<< orphan*/  V4L2_DEC_CMD_STOP ; 
 int V4L2_DEC_CMD_STOP_IMMEDIATELY ; 
 int V4L2_DEC_CMD_STOP_TO_BLACK ; 
#define  VIDEO_COMMAND 138 
#define  VIDEO_CONTINUE 137 
 int /*<<< orphan*/  VIDEO_EVENT_DECODER_STOPPED ; 
 int /*<<< orphan*/  VIDEO_EVENT_VSYNC ; 
#define  VIDEO_FREEZE 136 
#define  VIDEO_GET_EVENT 135 
#define  VIDEO_GET_EVENT32 134 
#define  VIDEO_GET_FRAME_COUNT 133 
#define  VIDEO_GET_PTS 132 
#define  VIDEO_PLAY 131 
#define  VIDEO_SELECT_SOURCE 130 
 unsigned long VIDEO_SOURCE_DEMUX ; 
#define  VIDEO_STOP 129 
#define  VIDEO_TRY_COMMAND 128 
 unsigned char VIDEO_VSYNC_FIELD_EVEN ; 
 unsigned char VIDEO_VSYNC_FIELD_ODD ; 
 unsigned char VIDEO_VSYNC_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  current ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ivtv_g_pts_frame (struct ivtv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ivtv_passthrough_mode (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_release_stream (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_set_output_mode (struct ivtv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_start_decoding (struct ivtv_open_id*,size_t) ; 
 int ivtv_video_command (struct ivtv*,struct ivtv_open_id*,struct video_event*,int) ; 
 int ivtv_yuv_prep_frame (struct ivtv*,struct ivtv_dma_frame*) ; 
 int /*<<< orphan*/  memset (struct video_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  warn_deprecated_ioctl (char*) ; 

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

#ifdef CONFIG_COMPAT
	case VIDEO_GET_EVENT32:
#endif
	case VIDEO_GET_EVENT: {
#ifdef CONFIG_COMPAT
		struct compat_video_event *ev32 = arg;
#endif
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
				unsigned char vsync_field;

				ev->type = VIDEO_EVENT_VSYNC;
				vsync_field = test_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags) ?
					VIDEO_VSYNC_FIELD_ODD : VIDEO_VSYNC_FIELD_EVEN;
				if (itv->output_mode == OUT_UDMA_YUV &&
					(itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) ==
								IVTV_YUV_MODE_PROGRESSIVE) {
					vsync_field = VIDEO_VSYNC_FIELD_PROGRESSIVE;
				}
#ifdef CONFIG_COMPAT
				if (cmd == VIDEO_GET_EVENT32)
					ev32->u.vsync_field = vsync_field;
				else
#endif
					ev->u.vsync_field = vsync_field;
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