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
struct TYPE_2__ {int vrefresh; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct nv17_tv_norm_params {TYPE_1__ tv_enc_mode; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;
struct drm_display_mode {scalar_t__ hdisplay; int clock; int htotal; int vtotal; int flags; scalar_t__ vdisplay; int /*<<< orphan*/  type; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 
 struct drm_display_mode* nv17_tv_modes ; 

__attribute__((used)) static int nv17_tv_get_ld_modes(struct drm_encoder *encoder,
				struct drm_connector *connector)
{
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	const struct drm_display_mode *tv_mode;
	int n = 0;

	for (tv_mode = nv17_tv_modes; tv_mode->hdisplay; tv_mode++) {
		struct drm_display_mode *mode;

		mode = drm_mode_duplicate(encoder->dev, tv_mode);

		mode->clock = tv_norm->tv_enc_mode.vrefresh *
			mode->htotal / 1000 *
			mode->vtotal / 1000;

		if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
			mode->clock *= 2;

		if (mode->hdisplay == tv_norm->tv_enc_mode.hdisplay &&
		    mode->vdisplay == tv_norm->tv_enc_mode.vdisplay)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		n++;
	}

	return n;
}