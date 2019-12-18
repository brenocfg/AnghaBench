#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num; int /*<<< orphan*/ * lock; int /*<<< orphan*/  tvnorms; int /*<<< orphan*/  release; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  fops; int /*<<< orphan*/  vfl_dir; TYPE_2__* v4l2_dev; int /*<<< orphan*/  name; } ;
struct ivtv_stream {int type; char* name; TYPE_3__ vdev; struct ivtv* itv; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_6__ {scalar_t__* kilobytes; } ;
struct ivtv {int instance; int v4l2_cap; int /*<<< orphan*/  serialize_lock; TYPE_2__ v4l2_dev; TYPE_1__ options; struct ivtv_stream* streams; } ;
struct TYPE_9__ {int num_offset; char* name; scalar_t__ dma; int v4l2_caps; int /*<<< orphan*/  fops; } ;

/* Variables and functions */
 int IVTV_DEC_STREAM_TYPE_MPG ; 
 int IVTV_DEC_STREAM_TYPE_VBI ; 
 int IVTV_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  IVTV_INFO (char*,char*) ; 
 scalar_t__ PCI_DMA_NONE ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_SLICED_VBI_OUTPUT ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VIDIOC_ENUMAUDIO ; 
 int /*<<< orphan*/  VIDIOC_ENUMINPUT ; 
 int /*<<< orphan*/  VIDIOC_G_AUDIO ; 
 int /*<<< orphan*/  VIDIOC_G_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_G_INPUT ; 
 int /*<<< orphan*/  VIDIOC_G_TUNER ; 
 int /*<<< orphan*/  VIDIOC_S_AUDIO ; 
 int /*<<< orphan*/  VIDIOC_S_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_S_INPUT ; 
 int /*<<< orphan*/  VIDIOC_S_STD ; 
 int /*<<< orphan*/  VIDIOC_S_TUNER ; 
 int ivtv_first_minor ; 
 int /*<<< orphan*/  ivtv_set_funcs (TYPE_3__*) ; 
 TYPE_4__* ivtv_stream_info ; 
 int /*<<< orphan*/  ivtv_stream_init (struct ivtv*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release_empty ; 

__attribute__((used)) static int ivtv_prep_dev(struct ivtv *itv, int type)
{
	struct ivtv_stream *s = &itv->streams[type];
	int num_offset = ivtv_stream_info[type].num_offset;
	int num = itv->instance + ivtv_first_minor + num_offset;

	/* These four fields are always initialized. If vdev.v4l2_dev == NULL, then
	   this stream is not in use. In that case no other fields but these
	   four can be used. */
	s->vdev.v4l2_dev = NULL;
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;

	/* Check whether the radio is supported */
	if (type == IVTV_ENC_STREAM_TYPE_RAD && !(itv->v4l2_cap & V4L2_CAP_RADIO))
		return 0;
	if (type >= IVTV_DEC_STREAM_TYPE_MPG && !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return 0;

	/* User explicitly selected 0 buffers for these streams, so don't
	   create them. */
	if (ivtv_stream_info[type].dma != PCI_DMA_NONE &&
	    itv->options.kilobytes[type] == 0) {
		IVTV_INFO("Disabled %s device\n", ivtv_stream_info[type].name);
		return 0;
	}

	ivtv_stream_init(itv, type);

	snprintf(s->vdev.name, sizeof(s->vdev.name), "%s %s",
			itv->v4l2_dev.name, s->name);

	s->vdev.num = num;
	s->vdev.v4l2_dev = &itv->v4l2_dev;
	if (ivtv_stream_info[type].v4l2_caps &
			(V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_SLICED_VBI_OUTPUT))
		s->vdev.vfl_dir = VFL_DIR_TX;
	s->vdev.fops = ivtv_stream_info[type].fops;
	s->vdev.ctrl_handler = itv->v4l2_dev.ctrl_handler;
	s->vdev.release = video_device_release_empty;
	s->vdev.tvnorms = V4L2_STD_ALL;
	s->vdev.lock = &itv->serialize_lock;
	if (s->type == IVTV_DEC_STREAM_TYPE_VBI) {
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMAUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMINPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_STD);
	}
	ivtv_set_funcs(&s->vdev);
	return 0;
}