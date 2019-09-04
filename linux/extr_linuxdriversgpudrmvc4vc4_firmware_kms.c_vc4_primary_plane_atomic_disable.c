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
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc4_plane_set_primary_blank (struct drm_plane*,int) ; 

__attribute__((used)) static void vc4_primary_plane_atomic_disable(struct drm_plane *plane,
					     struct drm_plane_state *old_state)
{
	vc4_plane_set_primary_blank(plane, true);
}