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
struct drm_plane {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_CURSOR ; 
 int EINVAL ; 

__attribute__((used)) static int dm_plane_atomic_async_check(struct drm_plane *plane,
				       struct drm_plane_state *new_plane_state)
{
	/* Only support async updates on cursor planes. */
	if (plane->type != DRM_PLANE_TYPE_CURSOR)
		return -EINVAL;

	return 0;
}