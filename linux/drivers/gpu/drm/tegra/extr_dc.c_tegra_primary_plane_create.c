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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_plane {int dummy; } ;
struct tegra_plane {int offset; struct drm_plane base; scalar_t__ index; struct tegra_dc* dc; } ;
struct tegra_dc {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_2__ {unsigned int num_primary_formats; int /*<<< orphan*/ * modifiers; int /*<<< orphan*/ * primary_formats; } ;

/* Variables and functions */
 int DRM_MODE_REFLECT_Y ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_plane_create_rotation_property (struct drm_plane*,int,int) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (struct drm_plane*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_plane*) ; 
 struct tegra_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_plane_funcs ; 
 unsigned long tegra_plane_get_possible_crtcs (struct drm_device*) ; 
 int /*<<< orphan*/  tegra_plane_helper_funcs ; 

__attribute__((used)) static struct drm_plane *tegra_primary_plane_create(struct drm_device *drm,
						    struct tegra_dc *dc)
{
	unsigned long possible_crtcs = tegra_plane_get_possible_crtcs(drm);
	enum drm_plane_type type = DRM_PLANE_TYPE_PRIMARY;
	struct tegra_plane *plane;
	unsigned int num_formats;
	const u64 *modifiers;
	const u32 *formats;
	int err;

	plane = kzalloc(sizeof(*plane), GFP_KERNEL);
	if (!plane)
		return ERR_PTR(-ENOMEM);

	/* Always use window A as primary window */
	plane->offset = 0xa00;
	plane->index = 0;
	plane->dc = dc;

	num_formats = dc->soc->num_primary_formats;
	formats = dc->soc->primary_formats;
	modifiers = dc->soc->modifiers;

	err = drm_universal_plane_init(drm, &plane->base, possible_crtcs,
				       &tegra_plane_funcs, formats,
				       num_formats, modifiers, type, NULL);
	if (err < 0) {
		kfree(plane);
		return ERR_PTR(err);
	}

	drm_plane_helper_add(&plane->base, &tegra_plane_helper_funcs);
	drm_plane_create_zpos_property(&plane->base, plane->index, 0, 255);

	err = drm_plane_create_rotation_property(&plane->base,
						 DRM_MODE_ROTATE_0,
						 DRM_MODE_ROTATE_0 |
						 DRM_MODE_REFLECT_Y);
	if (err < 0)
		dev_err(dc->dev, "failed to create rotation property: %d\n",
			err);

	return &plane->base;
}