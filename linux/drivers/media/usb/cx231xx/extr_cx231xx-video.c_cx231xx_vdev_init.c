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
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; } ;
struct cx231xx {char* name; scalar_t__ tuner_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  VIDIOC_G_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_G_TUNER ; 
 int /*<<< orphan*/  VIDIOC_S_FREQUENCY ; 
 int /*<<< orphan*/  VIDIOC_S_TUNER ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct cx231xx*) ; 

__attribute__((used)) static void cx231xx_vdev_init(struct cx231xx *dev,
		struct video_device *vfd,
		const struct video_device *template,
		const char *type_name)
{
	*vfd = *template;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &dev->lock;

	snprintf(vfd->name, sizeof(vfd->name), "%s %s", dev->name, type_name);

	video_set_drvdata(vfd, dev);
	if (dev->tuner_type == TUNER_ABSENT) {
		v4l2_disable_ioctl(vfd, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(vfd, VIDIOC_S_TUNER);
	}
}