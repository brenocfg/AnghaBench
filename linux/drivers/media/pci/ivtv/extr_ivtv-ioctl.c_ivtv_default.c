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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  newi2c; } ;
struct ivtv {int /*<<< orphan*/  sd_video; TYPE_1__ options; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct ivtv* itv; } ;

/* Variables and functions */
#define  AUDIO_BILINGUAL_CHANNEL_SELECT 143 
#define  AUDIO_CHANNEL_SELECT 142 
#define  AUDIO_SET_MUTE 141 
 long EBUSY ; 
 long ENOTTY ; 
#define  IVTV_IOC_DMA_FRAME 140 
#define  IVTV_IOC_PASSTHROUGH_MODE 139 
#define  VIDEO_COMMAND 138 
#define  VIDEO_CONTINUE 137 
#define  VIDEO_FREEZE 136 
#define  VIDEO_GET_EVENT 135 
#define  VIDEO_GET_FRAME_COUNT 134 
#define  VIDEO_GET_PTS 133 
#define  VIDEO_PLAY 132 
#define  VIDEO_SELECT_SOURCE 131 
#define  VIDEO_STOP 130 
#define  VIDEO_TRY_COMMAND 129 
#define  VIDIOC_INT_RESET 128 
 int /*<<< orphan*/  core ; 
 TYPE_2__* fh2id (void*) ; 
 long ivtv_decoder_ioctls (struct file*,unsigned int,void*) ; 
 int /*<<< orphan*/  ivtv_reset_ir_gpio (struct ivtv*) ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ivtv_default(struct file *file, void *fh, bool valid_prio,
			 unsigned int cmd, void *arg)
{
	struct ivtv *itv = fh2id(fh)->itv;

	if (!valid_prio) {
		switch (cmd) {
		case IVTV_IOC_PASSTHROUGH_MODE:
#ifdef CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
		case VIDEO_PLAY:
		case VIDEO_STOP:
		case VIDEO_FREEZE:
		case VIDEO_CONTINUE:
		case VIDEO_COMMAND:
		case VIDEO_SELECT_SOURCE:
		case AUDIO_SET_MUTE:
		case AUDIO_CHANNEL_SELECT:
		case AUDIO_BILINGUAL_CHANNEL_SELECT:
#endif
			return -EBUSY;
		}
	}

	switch (cmd) {
	case VIDIOC_INT_RESET: {
		u32 val = *(u32 *)arg;

		if ((val == 0 && itv->options.newi2c) || (val & 0x01))
			ivtv_reset_ir_gpio(itv);
		if (val & 0x02)
			v4l2_subdev_call(itv->sd_video, core, reset, 0);
		break;
	}

	case IVTV_IOC_DMA_FRAME:
	case IVTV_IOC_PASSTHROUGH_MODE:
#ifdef CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	case VIDEO_GET_PTS:
	case VIDEO_GET_FRAME_COUNT:
	case VIDEO_GET_EVENT:
	case VIDEO_PLAY:
	case VIDEO_STOP:
	case VIDEO_FREEZE:
	case VIDEO_CONTINUE:
	case VIDEO_COMMAND:
	case VIDEO_TRY_COMMAND:
	case VIDEO_SELECT_SOURCE:
	case AUDIO_SET_MUTE:
	case AUDIO_CHANNEL_SELECT:
	case AUDIO_BILINGUAL_CHANNEL_SELECT:
#endif
		return ivtv_decoder_ioctls(file, cmd, (void *)arg);

	default:
		return -ENOTTY;
	}
	return 0;
}