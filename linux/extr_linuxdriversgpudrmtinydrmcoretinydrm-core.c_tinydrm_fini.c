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
struct tinydrm_device {TYPE_1__* drm; int /*<<< orphan*/  dirty_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tinydrm_fini(struct tinydrm_device *tdev)
{
	drm_mode_config_cleanup(tdev->drm);
	mutex_destroy(&tdev->dirty_lock);
	tdev->drm->dev_private = NULL;
	drm_dev_unref(tdev->drm);
}