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
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 

__attribute__((used)) static void sti_cursor_destroy(struct drm_plane *drm_plane)
{
	DRM_DEBUG_DRIVER("\n");

	drm_plane_cleanup(drm_plane);
}