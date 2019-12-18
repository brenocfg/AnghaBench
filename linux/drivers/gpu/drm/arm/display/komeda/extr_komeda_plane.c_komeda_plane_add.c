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
typedef  int /*<<< orphan*/  u32 ;
struct drm_plane {int dummy; } ;
struct komeda_plane {struct komeda_layer* layer; struct drm_plane base; } ;
struct komeda_component {int /*<<< orphan*/  pipeline; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct komeda_layer {struct komeda_component base; int /*<<< orphan*/  supported_rots; int /*<<< orphan*/  layer_type; } ;
struct TYPE_2__ {struct komeda_dev* dev_private; } ;
struct komeda_kms_dev {TYPE_1__ base; } ;
struct komeda_dev {int /*<<< orphan*/  fmt_tbl; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT2020 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_FULL_RANGE ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_COVERAGE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PIXEL_NONE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PREMULTI ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_plane_create_alpha_property (struct drm_plane*) ; 
 int drm_plane_create_blend_mode_property (struct drm_plane*,int) ; 
 int drm_plane_create_color_properties (struct drm_plane*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_plane_create_rotation_property (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_plane_create_zpos_property (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (TYPE_1__*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_plane_type (struct komeda_kms_dev*,struct komeda_component*) ; 
 int /*<<< orphan*/  get_possible_crtcs (struct komeda_kms_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * komeda_get_layer_fourcc_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_plane_destroy (struct drm_plane*) ; 
 int /*<<< orphan*/  komeda_plane_funcs ; 
 int /*<<< orphan*/  komeda_plane_helper_funcs ; 
 int /*<<< orphan*/  komeda_put_fourcc_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_set_crtc_plane_mask (struct komeda_kms_dev*,int /*<<< orphan*/ ,struct drm_plane*) ; 
 int /*<<< orphan*/  komeda_supported_modifiers ; 
 struct komeda_plane* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int komeda_plane_add(struct komeda_kms_dev *kms,
			    struct komeda_layer *layer)
{
	struct komeda_dev *mdev = kms->base.dev_private;
	struct komeda_component *c = &layer->base;
	struct komeda_plane *kplane;
	struct drm_plane *plane;
	u32 *formats, n_formats = 0;
	int err;

	kplane = kzalloc(sizeof(*kplane), GFP_KERNEL);
	if (!kplane)
		return -ENOMEM;

	plane = &kplane->base;
	kplane->layer = layer;

	formats = komeda_get_layer_fourcc_list(&mdev->fmt_tbl,
					       layer->layer_type, &n_formats);

	err = drm_universal_plane_init(&kms->base, plane,
			get_possible_crtcs(kms, c->pipeline),
			&komeda_plane_funcs,
			formats, n_formats, komeda_supported_modifiers,
			get_plane_type(kms, c),
			"%s", c->name);

	komeda_put_fourcc_list(formats);

	if (err)
		goto cleanup;

	drm_plane_helper_add(plane, &komeda_plane_helper_funcs);

	err = drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
						 layer->supported_rots);
	if (err)
		goto cleanup;

	err = drm_plane_create_alpha_property(plane);
	if (err)
		goto cleanup;

	err = drm_plane_create_blend_mode_property(plane,
			BIT(DRM_MODE_BLEND_PIXEL_NONE) |
			BIT(DRM_MODE_BLEND_PREMULTI)   |
			BIT(DRM_MODE_BLEND_COVERAGE));
	if (err)
		goto cleanup;

	err = drm_plane_create_color_properties(plane,
			BIT(DRM_COLOR_YCBCR_BT601) |
			BIT(DRM_COLOR_YCBCR_BT709) |
			BIT(DRM_COLOR_YCBCR_BT2020),
			BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			BIT(DRM_COLOR_YCBCR_FULL_RANGE),
			DRM_COLOR_YCBCR_BT601,
			DRM_COLOR_YCBCR_LIMITED_RANGE);
	if (err)
		goto cleanup;

	err = drm_plane_create_zpos_property(plane, layer->base.id, 0, 8);
	if (err)
		goto cleanup;

	komeda_set_crtc_plane_mask(kms, c->pipeline, plane);

	return 0;
cleanup:
	komeda_plane_destroy(plane);
	return err;
}