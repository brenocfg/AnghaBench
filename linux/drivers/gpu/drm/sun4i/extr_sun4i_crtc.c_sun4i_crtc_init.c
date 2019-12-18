#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sunxi_engine {int dummy; } ;
struct sun4i_tcon {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct sun4i_crtc {TYPE_2__ crtc; struct sun4i_tcon* tcon; struct sunxi_engine* engine; } ;
struct drm_plane {int type; int /*<<< orphan*/  possible_crtcs; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
#define  DRM_PLANE_TYPE_CURSOR 129 
 scalar_t__ DRM_PLANE_TYPE_OVERLAY ; 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int ENOMEM ; 
 struct sun4i_crtc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_plane**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sun4i_crtc* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,TYPE_2__*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_mask (TYPE_2__*) ; 
 int /*<<< orphan*/  of_graph_get_port_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_crtc_funcs ; 
 int /*<<< orphan*/  sun4i_crtc_helper_funcs ; 
 struct drm_plane** sunxi_engine_layers_init (struct drm_device*,struct sunxi_engine*) ; 

struct sun4i_crtc *sun4i_crtc_init(struct drm_device *drm,
				   struct sunxi_engine *engine,
				   struct sun4i_tcon *tcon)
{
	struct sun4i_crtc *scrtc;
	struct drm_plane **planes;
	struct drm_plane *primary = NULL, *cursor = NULL;
	int ret, i;

	scrtc = devm_kzalloc(drm->dev, sizeof(*scrtc), GFP_KERNEL);
	if (!scrtc)
		return ERR_PTR(-ENOMEM);
	scrtc->engine = engine;
	scrtc->tcon = tcon;

	/* Create our layers */
	planes = sunxi_engine_layers_init(drm, engine);
	if (IS_ERR(planes)) {
		dev_err(drm->dev, "Couldn't create the planes\n");
		return NULL;
	}

	/* find primary and cursor planes for drm_crtc_init_with_planes */
	for (i = 0; planes[i]; i++) {
		struct drm_plane *plane = planes[i];

		switch (plane->type) {
		case DRM_PLANE_TYPE_PRIMARY:
			primary = plane;
			break;
		case DRM_PLANE_TYPE_CURSOR:
			cursor = plane;
			break;
		default:
			break;
		}
	}

	ret = drm_crtc_init_with_planes(drm, &scrtc->crtc,
					primary,
					cursor,
					&sun4i_crtc_funcs,
					NULL);
	if (ret) {
		dev_err(drm->dev, "Couldn't init DRM CRTC\n");
		return ERR_PTR(ret);
	}

	drm_crtc_helper_add(&scrtc->crtc, &sun4i_crtc_helper_funcs);

	/* Set crtc.port to output port node of the tcon */
	scrtc->crtc.port = of_graph_get_port_by_id(scrtc->tcon->dev->of_node,
						   1);

	/* Set possible_crtcs to this crtc for overlay planes */
	for (i = 0; planes[i]; i++) {
		uint32_t possible_crtcs = drm_crtc_mask(&scrtc->crtc);
		struct drm_plane *plane = planes[i];

		if (plane->type == DRM_PLANE_TYPE_OVERLAY)
			plane->possible_crtcs = possible_crtcs;
	}

	return scrtc;
}