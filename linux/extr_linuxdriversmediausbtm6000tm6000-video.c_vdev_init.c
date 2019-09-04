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
struct tm6000_core {char* name; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct tm6000_core*) ; 

__attribute__((used)) static void vdev_init(struct tm6000_core *dev,
		struct video_device *vfd,
		const struct video_device
		*template, const char *type_name)
{
	*vfd = *template;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &dev->lock;

	snprintf(vfd->name, sizeof(vfd->name), "%s %s", dev->name, type_name);

	video_set_drvdata(vfd, dev);
}