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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_plane {int dummy; } ;
struct TYPE_4__ {int offset; unsigned int index; struct drm_plane base; } ;
struct tegra_shared_plane {TYPE_2__ base; TYPE_1__* wgrp; } ;
struct tegra_drm {struct tegra_display_hub* hub; } ;
struct tegra_display_hub {TYPE_1__* wgrps; } ;
struct tegra_dc {int /*<<< orphan*/  dev; } ;
struct drm_device {struct tegra_drm* dev_private; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_shared_plane*) ; 
 struct tegra_shared_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_plane_funcs ; 
 int /*<<< orphan*/ * tegra_shared_plane_formats ; 
 int /*<<< orphan*/  tegra_shared_plane_helper_funcs ; 
 int /*<<< orphan*/ * tegra_shared_plane_modifiers ; 

struct drm_plane *tegra_shared_plane_create(struct drm_device *drm,
					    struct tegra_dc *dc,
					    unsigned int wgrp,
					    unsigned int index)
{
	enum drm_plane_type type = DRM_PLANE_TYPE_OVERLAY;
	struct tegra_drm *tegra = drm->dev_private;
	struct tegra_display_hub *hub = tegra->hub;
	/* planes can be assigned to arbitrary CRTCs */
	unsigned int possible_crtcs = 0x7;
	struct tegra_shared_plane *plane;
	unsigned int num_formats;
	const u64 *modifiers;
	struct drm_plane *p;
	const u32 *formats;
	int err;

	plane = kzalloc(sizeof(*plane), GFP_KERNEL);
	if (!plane)
		return ERR_PTR(-ENOMEM);

	plane->base.offset = 0x0a00 + 0x0300 * index;
	plane->base.index = index;

	plane->wgrp = &hub->wgrps[wgrp];
	plane->wgrp->parent = dc->dev;

	p = &plane->base.base;

	num_formats = ARRAY_SIZE(tegra_shared_plane_formats);
	formats = tegra_shared_plane_formats;
	modifiers = tegra_shared_plane_modifiers;

	err = drm_universal_plane_init(drm, p, possible_crtcs,
				       &tegra_plane_funcs, formats,
				       num_formats, modifiers, type, NULL);
	if (err < 0) {
		kfree(plane);
		return ERR_PTR(err);
	}

	drm_plane_helper_add(p, &tegra_shared_plane_helper_funcs);
	drm_plane_create_zpos_property(p, 0, 0, 255);

	return p;
}