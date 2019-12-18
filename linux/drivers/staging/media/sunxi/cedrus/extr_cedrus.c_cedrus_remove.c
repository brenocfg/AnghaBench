#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  devnode; } ;
struct cedrus_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vfd; int /*<<< orphan*/  m2m_dev; TYPE_1__ mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cedrus_hw_remove (struct cedrus_dev*) ; 
 int /*<<< orphan*/  media_device_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  media_device_unregister (TYPE_1__*) ; 
 scalar_t__ media_devnode_is_registered (int /*<<< orphan*/ ) ; 
 struct cedrus_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_unregister_media_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cedrus_remove(struct platform_device *pdev)
{
	struct cedrus_dev *dev = platform_get_drvdata(pdev);

	if (media_devnode_is_registered(dev->mdev.devnode)) {
		media_device_unregister(&dev->mdev);
		v4l2_m2m_unregister_media_controller(dev->m2m_dev);
		media_device_cleanup(&dev->mdev);
	}

	v4l2_m2m_release(dev->m2m_dev);
	video_unregister_device(&dev->vfd);
	v4l2_device_unregister(&dev->v4l2_dev);

	cedrus_hw_remove(dev);

	return 0;
}