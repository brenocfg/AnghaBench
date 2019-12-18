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
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/  release; int /*<<< orphan*/ * v4l2_dev; } ;
struct saa7134_dev {char* name; size_t board; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* saa7134_boards ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,char*) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct saa7134_dev*) ; 

__attribute__((used)) static struct video_device *vdev_init(struct saa7134_dev *dev,
				      struct video_device *template,
				      char *type)
{
	struct video_device *vfd;

	vfd = video_device_alloc();
	if (NULL == vfd)
		return NULL;
	*vfd = *template;
	vfd->v4l2_dev  = &dev->v4l2_dev;
	vfd->release = video_device_release;
	snprintf(vfd->name, sizeof(vfd->name), "%s %s (%s)",
		 dev->name, type, saa7134_boards[dev->board].name);
	video_set_drvdata(vfd, dev);
	return vfd;
}