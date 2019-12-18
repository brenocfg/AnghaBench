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
struct video_device {int device_caps; scalar_t__ tvnorms; int /*<<< orphan*/ * v4l2_dev; TYPE_2__* queue; int /*<<< orphan*/ * lock; } ;
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; } ;
struct go7007_buffer {int dummy; } ;
struct TYPE_4__ {int io_modes; int buf_struct_size; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; struct go7007* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct go7007 {int /*<<< orphan*/  dev; TYPE_1__* board_info; int /*<<< orphan*/  sd_video; int /*<<< orphan*/  v4l2_dev; TYPE_2__ vidq; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  vidq_active; struct video_device vdev; } ;
struct TYPE_3__ {scalar_t__ num_aud_inputs; int flags; int sensor_flags; } ;

/* Variables and functions */
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_SAA7115 ; 
 int GO7007_SENSOR_SCALING ; 
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAA7115_FREQ_24_576_MHZ ; 
 int SAA7115_FREQ_FL_APLL ; 
 int SAA7115_FREQ_FL_DOUBLE_ASCLK ; 
 int SAA7115_FREQ_FL_UCGC ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VIDIOC_ENUMAUDIO ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FRAMESIZES ; 
 int /*<<< orphan*/  VIDIOC_G_AUDIO ; 
 int /*<<< orphan*/  VIDIOC_G_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_G_STD ; 
 int /*<<< orphan*/  VIDIOC_G_TUNER ; 
 int /*<<< orphan*/  VIDIOC_QUERYSTD ; 
 int /*<<< orphan*/  VIDIOC_S_AUDIO ; 
 int /*<<< orphan*/  VIDIOC_S_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_S_STD ; 
 int /*<<< orphan*/  VIDIOC_S_TUNER ; 
 int /*<<< orphan*/  call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  go7007_s_input (struct go7007*) ; 
 int /*<<< orphan*/  go7007_s_std (struct go7007*) ; 
 struct video_device go7007_template ; 
 int /*<<< orphan*/  go7007_video_qops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  s_crystal_freq ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_has_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vb2_queue_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct go7007*) ; 

int go7007_v4l2_init(struct go7007 *go)
{
	struct video_device *vdev = &go->vdev;
	int rv;

	mutex_init(&go->serialize_lock);
	mutex_init(&go->queue_lock);

	INIT_LIST_HEAD(&go->vidq_active);
	go->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	go->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	go->vidq.ops = &go7007_video_qops;
	go->vidq.mem_ops = &vb2_vmalloc_memops;
	go->vidq.drv_priv = go;
	go->vidq.buf_struct_size = sizeof(struct go7007_buffer);
	go->vidq.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	go->vidq.lock = &go->queue_lock;
	rv = vb2_queue_init(&go->vidq);
	if (rv)
		return rv;
	*vdev = go7007_template;
	vdev->lock = &go->serialize_lock;
	vdev->queue = &go->vidq;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_STREAMING;
	if (go->board_info->num_aud_inputs)
		vdev->device_caps |= V4L2_CAP_AUDIO;
	if (go->board_info->flags & GO7007_BOARD_HAS_TUNER)
		vdev->device_caps |= V4L2_CAP_TUNER;
	video_set_drvdata(vdev, go);
	vdev->v4l2_dev = &go->v4l2_dev;
	if (!v4l2_device_has_op(&go->v4l2_dev, 0, video, querystd))
		v4l2_disable_ioctl(vdev, VIDIOC_QUERYSTD);
	if (!(go->board_info->flags & GO7007_BOARD_HAS_TUNER)) {
		v4l2_disable_ioctl(vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(vdev, VIDIOC_G_TUNER);
	} else {
		struct v4l2_frequency f = {
			.type = V4L2_TUNER_ANALOG_TV,
			.frequency = 980,
		};

		call_all(&go->v4l2_dev, tuner, s_frequency, &f);
	}
	if (!(go->board_info->sensor_flags & GO7007_SENSOR_TV)) {
		v4l2_disable_ioctl(vdev, VIDIOC_G_STD);
		v4l2_disable_ioctl(vdev, VIDIOC_S_STD);
		vdev->tvnorms = 0;
	}
	if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING)
		v4l2_disable_ioctl(vdev, VIDIOC_ENUM_FRAMESIZES);
	if (go->board_info->num_aud_inputs == 0) {
		v4l2_disable_ioctl(vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_ENUMAUDIO);
	}
	/* Setup correct crystal frequency on this board */
	if (go->board_info->sensor_flags & GO7007_SENSOR_SAA7115)
		v4l2_subdev_call(go->sd_video, video, s_crystal_freq,
				SAA7115_FREQ_24_576_MHZ,
				SAA7115_FREQ_FL_APLL | SAA7115_FREQ_FL_UCGC |
				SAA7115_FREQ_FL_DOUBLE_ASCLK);
	go7007_s_input(go);
	if (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		go7007_s_std(go);
	rv = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (rv < 0)
		return rv;
	dev_info(go->dev, "registered device %s [v4l2]\n",
		 video_device_node_name(vdev));

	return 0;
}