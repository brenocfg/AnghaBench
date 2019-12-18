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
struct video_device {int /*<<< orphan*/  name; scalar_t__ tvnorms; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * v4l2_dev; } ;
struct em28xx {TYPE_2__* intf; scalar_t__ is_webcam; int /*<<< orphan*/  lock; TYPE_1__* v4l2; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct em28xx*) ; 

__attribute__((used)) static void em28xx_vdev_init(struct em28xx *dev,
			     struct video_device *vfd,
			     const struct video_device *template,
			     const char *type_name)
{
	*vfd		= *template;
	vfd->v4l2_dev	= &dev->v4l2->v4l2_dev;
	vfd->lock	= &dev->lock;
	if (dev->is_webcam)
		vfd->tvnorms = 0;

	snprintf(vfd->name, sizeof(vfd->name), "%s %s",
		 dev_name(&dev->intf->dev), type_name);

	video_set_drvdata(vfd, dev);
}