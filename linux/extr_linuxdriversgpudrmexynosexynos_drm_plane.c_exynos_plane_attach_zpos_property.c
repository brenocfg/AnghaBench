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
 scalar_t__ MAX_PLANE ; 
 int /*<<< orphan*/  drm_plane_create_zpos_immutable_property (struct drm_plane*,int) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (struct drm_plane*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void exynos_plane_attach_zpos_property(struct drm_plane *plane,
					      int zpos, bool immutable)
{
	if (immutable)
		drm_plane_create_zpos_immutable_property(plane, zpos);
	else
		drm_plane_create_zpos_property(plane, zpos, 0, MAX_PLANE - 1);
}