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
struct omap_plane {int /*<<< orphan*/  name; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (struct omap_plane*) ; 
 struct omap_plane* to_omap_plane (struct drm_plane*) ; 

__attribute__((used)) static void omap_plane_destroy(struct drm_plane *plane)
{
	struct omap_plane *omap_plane = to_omap_plane(plane);

	DBG("%s", omap_plane->name);

	drm_plane_cleanup(plane);

	kfree(omap_plane);
}