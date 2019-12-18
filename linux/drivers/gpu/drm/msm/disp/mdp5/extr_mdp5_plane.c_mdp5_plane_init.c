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
struct drm_plane {int /*<<< orphan*/  base; } ;
struct mdp5_plane {int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; struct drm_plane base; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_enable_fb_damage_clips (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct mdp5_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_plane_destroy (struct drm_plane*) ; 
 int /*<<< orphan*/  mdp5_plane_funcs ; 
 int /*<<< orphan*/  mdp5_plane_helper_funcs ; 
 int /*<<< orphan*/  mdp5_plane_install_properties (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp_get_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct drm_plane *mdp5_plane_init(struct drm_device *dev,
				  enum drm_plane_type type)
{
	struct drm_plane *plane = NULL;
	struct mdp5_plane *mdp5_plane;
	int ret;

	mdp5_plane = kzalloc(sizeof(*mdp5_plane), GFP_KERNEL);
	if (!mdp5_plane) {
		ret = -ENOMEM;
		goto fail;
	}

	plane = &mdp5_plane->base;

	mdp5_plane->nformats = mdp_get_formats(mdp5_plane->formats,
		ARRAY_SIZE(mdp5_plane->formats), false);

	ret = drm_universal_plane_init(dev, plane, 0xff, &mdp5_plane_funcs,
			mdp5_plane->formats, mdp5_plane->nformats,
			NULL, type, NULL);
	if (ret)
		goto fail;

	drm_plane_helper_add(plane, &mdp5_plane_helper_funcs);

	mdp5_plane_install_properties(plane, &plane->base);

	drm_plane_enable_fb_damage_clips(plane);

	return plane;

fail:
	if (plane)
		mdp5_plane_destroy(plane);

	return ERR_PTR(ret);
}