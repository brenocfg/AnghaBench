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
typedef  int u32 ;
struct sun8i_vi_layer {int channel; scalar_t__ overlay; struct sun8i_mixer* mixer; int /*<<< orphan*/  plane; } ;
struct sun8i_mixer {TYPE_1__* cfg; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int ui_num; unsigned int vi_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_FULL_RANGE ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int ENOMEM ; 
 struct sun8i_vi_layer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sun8i_vi_layer* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_plane_create_color_properties (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_plane_create_zpos_property (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun8i_vi_layer_formats ; 
 int /*<<< orphan*/  sun8i_vi_layer_funcs ; 
 int /*<<< orphan*/  sun8i_vi_layer_helper_funcs ; 

struct sun8i_vi_layer *sun8i_vi_layer_init_one(struct drm_device *drm,
					       struct sun8i_mixer *mixer,
					       int index)
{
	u32 supported_encodings, supported_ranges;
	struct sun8i_vi_layer *layer;
	unsigned int plane_cnt;
	int ret;

	layer = devm_kzalloc(drm->dev, sizeof(*layer), GFP_KERNEL);
	if (!layer)
		return ERR_PTR(-ENOMEM);

	/* possible crtcs are set later */
	ret = drm_universal_plane_init(drm, &layer->plane, 0,
				       &sun8i_vi_layer_funcs,
				       sun8i_vi_layer_formats,
				       ARRAY_SIZE(sun8i_vi_layer_formats),
				       NULL, DRM_PLANE_TYPE_OVERLAY, NULL);
	if (ret) {
		dev_err(drm->dev, "Couldn't initialize layer\n");
		return ERR_PTR(ret);
	}

	plane_cnt = mixer->cfg->ui_num + mixer->cfg->vi_num;

	ret = drm_plane_create_zpos_property(&layer->plane, index,
					     0, plane_cnt - 1);
	if (ret) {
		dev_err(drm->dev, "Couldn't add zpos property\n");
		return ERR_PTR(ret);
	}

	supported_encodings = BIT(DRM_COLOR_YCBCR_BT601) |
			      BIT(DRM_COLOR_YCBCR_BT709);

	supported_ranges = BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			   BIT(DRM_COLOR_YCBCR_FULL_RANGE);

	ret = drm_plane_create_color_properties(&layer->plane,
						supported_encodings,
						supported_ranges,
						DRM_COLOR_YCBCR_BT709,
						DRM_COLOR_YCBCR_LIMITED_RANGE);
	if (ret) {
		dev_err(drm->dev, "Couldn't add encoding and range properties!\n");
		return ERR_PTR(ret);
	}

	drm_plane_helper_add(&layer->plane, &sun8i_vi_layer_helper_funcs);
	layer->mixer = mixer;
	layer->channel = index;
	layer->overlay = 0;

	return layer;
}