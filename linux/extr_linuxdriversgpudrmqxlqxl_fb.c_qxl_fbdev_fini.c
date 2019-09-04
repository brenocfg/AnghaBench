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
struct TYPE_2__ {int /*<<< orphan*/ * qfbdev; } ;
struct qxl_device {TYPE_1__ mode_info; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_fbdev_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qxl_fbdev_fini(struct qxl_device *qdev)
{
	if (!qdev->mode_info.qfbdev)
		return;

	qxl_fbdev_destroy(&qdev->ddev, qdev->mode_info.qfbdev);
	kfree(qdev->mode_info.qfbdev);
	qdev->mode_info.qfbdev = NULL;
}