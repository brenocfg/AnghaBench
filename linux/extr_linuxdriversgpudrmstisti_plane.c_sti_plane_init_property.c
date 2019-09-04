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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct sti_plane {TYPE_2__ drm_plane; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_plane_attach_zorder_property (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sti_plane_to_str (struct sti_plane*) ; 

void sti_plane_init_property(struct sti_plane *plane,
			     enum drm_plane_type type)
{
	sti_plane_attach_zorder_property(&plane->drm_plane, type);

	DRM_DEBUG_DRIVER("drm plane:%d mapped to %s\n",
			 plane->drm_plane.base.id, sti_plane_to_str(plane));
}