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
struct nouveau_display {int /*<<< orphan*/ * suspend; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_resume (struct drm_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_init (struct drm_device*,int,int) ; 

void
nouveau_display_resume(struct drm_device *dev, bool runtime)
{
	struct nouveau_display *disp = nouveau_display(dev);

	nouveau_display_init(dev, true, runtime);

	if (drm_drv_uses_atomic_modeset(dev)) {
		if (disp->suspend) {
			drm_atomic_helper_resume(dev, disp->suspend);
			disp->suspend = NULL;
		}
		return;
	}
}