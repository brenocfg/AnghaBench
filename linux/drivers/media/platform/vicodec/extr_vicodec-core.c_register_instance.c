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
struct video_device {int device_caps; int /*<<< orphan*/  num; int /*<<< orphan*/  name; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct vicodec_dev_instance {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  mutex; struct video_device vfd; int /*<<< orphan*/  lock; } ;
struct vicodec_dev {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VIDIOC_DECODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_ENCODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_TRY_DECODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_TRY_ENCODER_CMD ; 
 int /*<<< orphan*/  m2m_ops ; 
 scalar_t__ multiplanar ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 struct video_device vicodec_videodev ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct vicodec_dev*) ; 

__attribute__((used)) static int register_instance(struct vicodec_dev *dev,
			     struct vicodec_dev_instance *dev_instance,
			     const char *name, bool is_enc)
{
	struct video_device *vfd;
	int ret;

	spin_lock_init(&dev_instance->lock);
	mutex_init(&dev_instance->mutex);
	dev_instance->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(dev_instance->m2m_dev)) {
		v4l2_err(&dev->v4l2_dev, "Failed to init vicodec enc device\n");
		return PTR_ERR(dev_instance->m2m_dev);
	}

	dev_instance->vfd = vicodec_videodev;
	vfd = &dev_instance->vfd;
	vfd->lock = &dev_instance->mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;
	strscpy(vfd->name, name, sizeof(vfd->name));
	vfd->device_caps = V4L2_CAP_STREAMING |
		(multiplanar ? V4L2_CAP_VIDEO_M2M_MPLANE : V4L2_CAP_VIDEO_M2M);
	if (is_enc) {
		v4l2_disable_ioctl(vfd, VIDIOC_DECODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_DECODER_CMD);
	} else {
		v4l2_disable_ioctl(vfd, VIDIOC_ENCODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_ENCODER_CMD);
	}
	video_set_drvdata(vfd, dev);

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register video device '%s'\n", name);
		v4l2_m2m_release(dev_instance->m2m_dev);
		return ret;
	}
	v4l2_info(&dev->v4l2_dev, "Device '%s' registered as /dev/video%d\n",
		  name, vfd->num);
	return 0;
}