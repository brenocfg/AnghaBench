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
struct drm_plane {int dummy; } ;
struct meson_plane {struct drm_plane base; struct meson_drm* priv; } ;
struct meson_drm {struct drm_plane* primary_plane; TYPE_1__* drm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct meson_plane* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_immutable_property (struct drm_plane*,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_universal_plane_init (TYPE_1__*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  meson_plane_funcs ; 
 int /*<<< orphan*/  meson_plane_helper_funcs ; 
 int /*<<< orphan*/  supported_drm_formats ; 

int meson_plane_create(struct meson_drm *priv)
{
	struct meson_plane *meson_plane;
	struct drm_plane *plane;

	meson_plane = devm_kzalloc(priv->drm->dev, sizeof(*meson_plane),
				   GFP_KERNEL);
	if (!meson_plane)
		return -ENOMEM;

	meson_plane->priv = priv;
	plane = &meson_plane->base;

	drm_universal_plane_init(priv->drm, plane, 0xFF,
				 &meson_plane_funcs,
				 supported_drm_formats,
				 ARRAY_SIZE(supported_drm_formats),
				 NULL,
				 DRM_PLANE_TYPE_PRIMARY, "meson_primary_plane");

	drm_plane_helper_add(plane, &meson_plane_helper_funcs);

	/* For now, OSD Primary plane is always on the front */
	drm_plane_create_zpos_immutable_property(plane, 1);

	priv->primary_plane = plane;

	return 0;
}