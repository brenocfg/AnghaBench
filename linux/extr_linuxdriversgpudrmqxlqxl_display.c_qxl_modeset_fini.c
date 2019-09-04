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
struct TYPE_2__ {int mode_config_initialized; } ;
struct qxl_device {TYPE_1__ mode_info; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_destroy_monitors_object (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_fbdev_fini (struct qxl_device*) ; 

void qxl_modeset_fini(struct qxl_device *qdev)
{
	qxl_fbdev_fini(qdev);

	qxl_destroy_monitors_object(qdev);
	if (qdev->mode_info.mode_config_initialized) {
		drm_mode_config_cleanup(&qdev->ddev);
		qdev->mode_info.mode_config_initialized = false;
	}
}