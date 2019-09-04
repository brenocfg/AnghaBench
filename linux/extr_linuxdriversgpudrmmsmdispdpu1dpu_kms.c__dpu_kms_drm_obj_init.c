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
struct msm_drm_private {int num_encoders; int num_crtcs; TYPE_2__** encoders; struct drm_plane** crtcs; int /*<<< orphan*/  num_planes; struct drm_plane** planes; } ;
struct drm_plane {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; int /*<<< orphan*/  dev; } ;
typedef  struct drm_plane drm_crtc ;
struct dpu_mdss_cfg {int mixer_count; int sspp_count; TYPE_1__* sspp; } ;
struct dpu_kms {struct dpu_mdss_cfg* catalog; struct drm_device* dev; } ;
struct TYPE_4__ {int possible_crtcs; } ;
struct TYPE_3__ {int features; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_SSPP_CURSOR ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int MAX_PLANES ; 
 int PTR_ERR (struct drm_plane*) ; 
 int /*<<< orphan*/  _dpu_kms_drm_obj_destroy (struct dpu_kms*) ; 
 int /*<<< orphan*/  _dpu_kms_setup_displays (struct drm_device*,struct msm_drm_private*,struct dpu_kms*) ; 
 struct drm_plane* dpu_crtc_init (struct drm_device*,struct drm_plane*) ; 
 struct drm_plane* dpu_plane_init (struct drm_device*,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static int _dpu_kms_drm_obj_init(struct dpu_kms *dpu_kms)
{
	struct drm_device *dev;
	struct drm_plane *primary_planes[MAX_PLANES], *plane;
	struct drm_crtc *crtc;

	struct msm_drm_private *priv;
	struct dpu_mdss_cfg *catalog;

	int primary_planes_idx = 0, i, ret;
	int max_crtc_count;

	if (!dpu_kms || !dpu_kms->dev || !dpu_kms->dev->dev) {
		DPU_ERROR("invalid dpu_kms\n");
		return -EINVAL;
	}

	dev = dpu_kms->dev;
	priv = dev->dev_private;
	catalog = dpu_kms->catalog;

	/*
	 * Create encoder and query display drivers to create
	 * bridges and connectors
	 */
	_dpu_kms_setup_displays(dev, priv, dpu_kms);

	max_crtc_count = min(catalog->mixer_count, priv->num_encoders);

	/* Create the planes */
	for (i = 0; i < catalog->sspp_count; i++) {
		bool primary = true;

		if (catalog->sspp[i].features & BIT(DPU_SSPP_CURSOR)
			|| primary_planes_idx >= max_crtc_count)
			primary = false;

		plane = dpu_plane_init(dev, catalog->sspp[i].id, primary,
				(1UL << max_crtc_count) - 1, 0);
		if (IS_ERR(plane)) {
			DPU_ERROR("dpu_plane_init failed\n");
			ret = PTR_ERR(plane);
			goto fail;
		}
		priv->planes[priv->num_planes++] = plane;

		if (primary)
			primary_planes[primary_planes_idx++] = plane;
	}

	max_crtc_count = min(max_crtc_count, primary_planes_idx);

	/* Create one CRTC per encoder */
	for (i = 0; i < max_crtc_count; i++) {
		crtc = dpu_crtc_init(dev, primary_planes[i]);
		if (IS_ERR(crtc)) {
			ret = PTR_ERR(crtc);
			goto fail;
		}
		priv->crtcs[priv->num_crtcs++] = crtc;
	}

	/* All CRTCs are compatible with all encoders */
	for (i = 0; i < priv->num_encoders; i++)
		priv->encoders[i]->possible_crtcs = (1 << priv->num_crtcs) - 1;

	return 0;
fail:
	_dpu_kms_drm_obj_destroy(dpu_kms);
	return ret;
}