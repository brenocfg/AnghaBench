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
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int port_clock; int lspcon_downsampling; int /*<<< orphan*/  output_format; TYPE_1__ base; } ;
struct drm_display_info {int dummy; } ;
struct drm_connector {scalar_t__ ycbcr_420_allowed; struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_YCBCR444 ; 
 scalar_t__ drm_mode_is_420_only (struct drm_display_info const*,struct drm_display_mode const*) ; 

void lspcon_ycbcr420_config(struct drm_connector *connector,
			    struct intel_crtc_state *crtc_state)
{
	const struct drm_display_info *info = &connector->display_info;
	const struct drm_display_mode *adjusted_mode =
					&crtc_state->base.adjusted_mode;

	if (drm_mode_is_420_only(info, adjusted_mode) &&
	    connector->ycbcr_420_allowed) {
		crtc_state->port_clock /= 2;
		crtc_state->output_format = INTEL_OUTPUT_FORMAT_YCBCR444;
		crtc_state->lspcon_downsampling = true;
	}
}