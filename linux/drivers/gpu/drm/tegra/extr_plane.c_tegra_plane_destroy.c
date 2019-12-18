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
struct tegra_plane {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (struct tegra_plane*) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 

__attribute__((used)) static void tegra_plane_destroy(struct drm_plane *plane)
{
	struct tegra_plane *p = to_tegra_plane(plane);

	drm_plane_cleanup(plane);
	kfree(p);
}