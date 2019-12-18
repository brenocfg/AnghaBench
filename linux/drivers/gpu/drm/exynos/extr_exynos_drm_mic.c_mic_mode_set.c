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
struct exynos_mic {int /*<<< orphan*/  i80_mode; int /*<<< orphan*/  vm; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {TYPE_1__* encoder; struct exynos_mic* driver_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  i80_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mic_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_exynos_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_mode_set(struct drm_bridge *bridge,
			 const struct drm_display_mode *mode,
			 const struct drm_display_mode *adjusted_mode)
{
	struct exynos_mic *mic = bridge->driver_private;

	mutex_lock(&mic_mutex);
	drm_display_mode_to_videomode(mode, &mic->vm);
	mic->i80_mode = to_exynos_crtc(bridge->encoder->crtc)->i80_mode;
	mutex_unlock(&mic_mutex);
}