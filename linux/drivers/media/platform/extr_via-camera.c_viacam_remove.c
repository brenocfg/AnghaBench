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
struct viafb_dev {TYPE_2__* pdev; } ;
struct via_camera {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vdev; } ;
struct TYPE_3__ {struct viafb_dev* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct via_camera*) ; 
 int /*<<< orphan*/  kfree (struct via_camera*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 struct via_camera* via_cam_info ; 
 int /*<<< orphan*/  via_sensor_power_release (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_pm_hooks ; 
 int /*<<< orphan*/  viafb_pm_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_remove(struct platform_device *pdev)
{
	struct via_camera *cam = via_cam_info;
	struct viafb_dev *viadev = pdev->dev.platform_data;

	video_unregister_device(&cam->vdev);
	v4l2_device_unregister(&cam->v4l2_dev);
#ifdef CONFIG_PM
	viafb_pm_unregister(&viacam_pm_hooks);
#endif
	free_irq(viadev->pdev->irq, cam);
	via_sensor_power_release(cam);
	v4l2_ctrl_handler_free(&cam->ctrl_handler);
	kfree(cam);
	via_cam_info = NULL;
	return 0;
}