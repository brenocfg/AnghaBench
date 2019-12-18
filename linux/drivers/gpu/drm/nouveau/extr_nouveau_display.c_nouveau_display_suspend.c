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
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drm_atomic_helper_suspend (struct drm_device*) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_display_fini (struct drm_device*,int,int) ; 

int
nouveau_display_suspend(struct drm_device *dev, bool runtime)
{
	struct nouveau_display *disp = nouveau_display(dev);

	if (drm_drv_uses_atomic_modeset(dev)) {
		if (!runtime) {
			disp->suspend = drm_atomic_helper_suspend(dev);
			if (IS_ERR(disp->suspend)) {
				int ret = PTR_ERR(disp->suspend);
				disp->suspend = NULL;
				return ret;
			}
		}
	}

	nouveau_display_fini(dev, true, runtime);
	return 0;
}