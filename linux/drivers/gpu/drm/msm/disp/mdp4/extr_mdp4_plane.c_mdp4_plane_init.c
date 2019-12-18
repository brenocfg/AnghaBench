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
struct mdp4_plane {int pipe; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; int /*<<< orphan*/  caps; int /*<<< orphan*/  name; struct drm_plane base; } ;
struct drm_device {int dummy; } ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_enable_fb_damage_clips (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct mdp4_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_pipe_caps (int) ; 
 int /*<<< orphan*/  mdp4_plane_destroy (struct drm_plane*) ; 
 int /*<<< orphan*/  mdp4_plane_funcs ; 
 int /*<<< orphan*/  mdp4_plane_helper_funcs ; 
 int /*<<< orphan*/  mdp4_plane_install_properties (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp_get_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pipe_names ; 
 int /*<<< orphan*/  pipe_supports_yuv (int /*<<< orphan*/ ) ; 

struct drm_plane *mdp4_plane_init(struct drm_device *dev,
		enum mdp4_pipe pipe_id, bool private_plane)
{
	struct drm_plane *plane = NULL;
	struct mdp4_plane *mdp4_plane;
	int ret;
	enum drm_plane_type type;

	mdp4_plane = kzalloc(sizeof(*mdp4_plane), GFP_KERNEL);
	if (!mdp4_plane) {
		ret = -ENOMEM;
		goto fail;
	}

	plane = &mdp4_plane->base;

	mdp4_plane->pipe = pipe_id;
	mdp4_plane->name = pipe_names[pipe_id];
	mdp4_plane->caps = mdp4_pipe_caps(pipe_id);

	mdp4_plane->nformats = mdp_get_formats(mdp4_plane->formats,
			ARRAY_SIZE(mdp4_plane->formats),
			!pipe_supports_yuv(mdp4_plane->caps));

	type = private_plane ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
	ret = drm_universal_plane_init(dev, plane, 0xff, &mdp4_plane_funcs,
				 mdp4_plane->formats, mdp4_plane->nformats,
				 NULL, type, NULL);
	if (ret)
		goto fail;

	drm_plane_helper_add(plane, &mdp4_plane_helper_funcs);

	mdp4_plane_install_properties(plane, &plane->base);

	drm_plane_enable_fb_damage_clips(plane);

	return plane;

fail:
	if (plane)
		mdp4_plane_destroy(plane);

	return ERR_PTR(ret);
}