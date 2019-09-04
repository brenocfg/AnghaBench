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
struct intel_crtc_state {int pipe_bpp; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_display_info {int bpc; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ base; struct drm_display_info display_info; } ;
struct intel_connector {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 

__attribute__((used)) static void
connected_sink_compute_bpp(struct intel_connector *connector,
			   struct intel_crtc_state *pipe_config)
{
	const struct drm_display_info *info = &connector->base.display_info;
	int bpp = pipe_config->pipe_bpp;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] checking for sink bpp constrains\n",
		      connector->base.base.id,
		      connector->base.name);

	/* Don't use an invalid EDID bpc value */
	if (info->bpc != 0 && info->bpc * 3 < bpp) {
		DRM_DEBUG_KMS("clamping display bpp (was %d) to EDID reported max of %d\n",
			      bpp, info->bpc * 3);
		pipe_config->pipe_bpp = info->bpc * 3;
	}

	/* Clamp bpp to 8 on screens without EDID 1.4 */
	if (info->bpc == 0 && bpp > 24) {
		DRM_DEBUG_KMS("clamping display bpp (was %d) to default limit of 24\n",
			      bpp);
		pipe_config->pipe_bpp = 24;
	}
}