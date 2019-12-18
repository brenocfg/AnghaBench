#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {struct atmel_hlcdc_dc* dev_private; } ;
struct TYPE_6__ {int possible_crtcs; } ;
struct atmel_hlcdc_plane {TYPE_2__ base; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/ * crtc; TYPE_4__** layers; } ;
struct atmel_hlcdc_crtc {int id; int /*<<< orphan*/  base; struct atmel_hlcdc_dc* dc; } ;
struct TYPE_7__ {TYPE_1__* desc; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
#define  ATMEL_HLCDC_BASE_LAYER 129 
 int /*<<< orphan*/  ATMEL_HLCDC_CLUT_SIZE ; 
#define  ATMEL_HLCDC_CURSOR_LAYER 128 
 int ATMEL_HLCDC_MAX_LAYERS ; 
 int ATMEL_HLCDC_OVERLAY_LAYER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atmel_hlcdc_crtc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmel_hlcdc_crtc_funcs ; 
 struct atmel_hlcdc_plane* atmel_hlcdc_layer_to_plane (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_crtc_enable_color_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_crtc_index (int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atmel_hlcdc_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_crtc_helper_funcs ; 

int atmel_hlcdc_crtc_create(struct drm_device *dev)
{
	struct atmel_hlcdc_plane *primary = NULL, *cursor = NULL;
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	struct atmel_hlcdc_crtc *crtc;
	int ret;
	int i;

	crtc = kzalloc(sizeof(*crtc), GFP_KERNEL);
	if (!crtc)
		return -ENOMEM;

	crtc->dc = dc;

	for (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) {
		if (!dc->layers[i])
			continue;

		switch (dc->layers[i]->desc->type) {
		case ATMEL_HLCDC_BASE_LAYER:
			primary = atmel_hlcdc_layer_to_plane(dc->layers[i]);
			break;

		case ATMEL_HLCDC_CURSOR_LAYER:
			cursor = atmel_hlcdc_layer_to_plane(dc->layers[i]);
			break;

		default:
			break;
		}
	}

	ret = drm_crtc_init_with_planes(dev, &crtc->base, &primary->base,
					&cursor->base, &atmel_hlcdc_crtc_funcs,
					NULL);
	if (ret < 0)
		goto fail;

	crtc->id = drm_crtc_index(&crtc->base);

	for (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) {
		struct atmel_hlcdc_plane *overlay;

		if (dc->layers[i] &&
		    dc->layers[i]->desc->type == ATMEL_HLCDC_OVERLAY_LAYER) {
			overlay = atmel_hlcdc_layer_to_plane(dc->layers[i]);
			overlay->base.possible_crtcs = 1 << crtc->id;
		}
	}

	drm_crtc_helper_add(&crtc->base, &lcdc_crtc_helper_funcs);
	drm_crtc_vblank_reset(&crtc->base);

	drm_mode_crtc_set_gamma_size(&crtc->base, ATMEL_HLCDC_CLUT_SIZE);
	drm_crtc_enable_color_mgmt(&crtc->base, 0, false,
				   ATMEL_HLCDC_CLUT_SIZE);

	dc->crtc = &crtc->base;

	return 0;

fail:
	atmel_hlcdc_crtc_destroy(&crtc->base);
	return ret;
}