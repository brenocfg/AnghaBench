#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct rcar_du_plane {TYPE_2__ plane; struct rcar_du_group* group; } ;
struct rcar_du_group {int num_planes; int num_crtcs; int index; struct rcar_du_plane* planes; struct rcar_du_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  colorkey; } ;
struct rcar_du_device {int num_crtcs; TYPE_1__ props; int /*<<< orphan*/  ddev; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  RCAR_DU_COLORKEY_NONE ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ ,TYPE_2__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  formats ; 
 int /*<<< orphan*/  rcar_du_plane_funcs ; 
 int /*<<< orphan*/  rcar_du_plane_helper_funcs ; 

int rcar_du_planes_init(struct rcar_du_group *rgrp)
{
	struct rcar_du_device *rcdu = rgrp->dev;
	unsigned int crtcs;
	unsigned int i;
	int ret;

	 /*
	  * Create one primary plane per CRTC in this group and seven overlay
	  * planes.
	  */
	rgrp->num_planes = rgrp->num_crtcs + 7;

	crtcs = ((1 << rcdu->num_crtcs) - 1) & (3 << (2 * rgrp->index));

	for (i = 0; i < rgrp->num_planes; ++i) {
		enum drm_plane_type type = i < rgrp->num_crtcs
					 ? DRM_PLANE_TYPE_PRIMARY
					 : DRM_PLANE_TYPE_OVERLAY;
		struct rcar_du_plane *plane = &rgrp->planes[i];

		plane->group = rgrp;

		ret = drm_universal_plane_init(rcdu->ddev, &plane->plane, crtcs,
					       &rcar_du_plane_funcs, formats,
					       ARRAY_SIZE(formats),
					       NULL, type, NULL);
		if (ret < 0)
			return ret;

		drm_plane_helper_add(&plane->plane,
				     &rcar_du_plane_helper_funcs);

		drm_plane_create_alpha_property(&plane->plane);

		if (type == DRM_PLANE_TYPE_PRIMARY)
			continue;

		drm_object_attach_property(&plane->plane.base,
					   rcdu->props.colorkey,
					   RCAR_DU_COLORKEY_NONE);
		drm_plane_create_zpos_property(&plane->plane, 1, 1, 7);
	}

	return 0;
}