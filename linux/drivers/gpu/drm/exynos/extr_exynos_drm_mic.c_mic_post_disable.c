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
struct exynos_mic {scalar_t__ enabled; int /*<<< orphan*/  dev; } ;
struct drm_bridge {struct exynos_mic* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_mutex ; 
 int /*<<< orphan*/  mic_set_path (struct exynos_mic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_post_disable(struct drm_bridge *bridge)
{
	struct exynos_mic *mic = bridge->driver_private;

	mutex_lock(&mic_mutex);
	if (!mic->enabled)
		goto already_disabled;

	mic_set_path(mic, 0);

	pm_runtime_put(mic->dev);
	mic->enabled = 0;

already_disabled:
	mutex_unlock(&mic_mutex);
}