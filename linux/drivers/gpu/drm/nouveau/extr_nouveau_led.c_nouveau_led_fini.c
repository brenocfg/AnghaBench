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
struct nouveau_drm {TYPE_1__* led; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  led; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

void
nouveau_led_fini(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (drm->led) {
		led_classdev_unregister(&drm->led->led);
		kfree(drm->led);
		drm->led = NULL;
	}
}