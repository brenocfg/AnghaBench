#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_property {int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int
intel_plane_atomic_get_property(struct drm_plane *plane,
				const struct drm_plane_state *state,
				struct drm_property *property,
				uint64_t *val)
{
	DRM_DEBUG_KMS("Unknown property [PROP:%d:%s]\n",
		      property->base.id, property->name);
	return -EINVAL;
}