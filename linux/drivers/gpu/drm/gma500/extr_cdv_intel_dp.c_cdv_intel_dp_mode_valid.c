#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct TYPE_6__ {int bpp; } ;
struct drm_psb_private {TYPE_3__ edp; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; int clock; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct cdv_intel_dp {TYPE_2__* panel_fixed_mode; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_5__ {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct TYPE_4__ {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 int cdv_intel_dp_link_clock (int /*<<< orphan*/ ) ; 
 scalar_t__ cdv_intel_dp_link_required (int,int) ; 
 scalar_t__ cdv_intel_dp_max_data_rate (int,int) ; 
 int cdv_intel_dp_max_lane_count (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_max_link_bw (struct gma_encoder*) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 scalar_t__ is_edp (struct gma_encoder*) ; 

__attribute__((used)) static enum drm_mode_status
cdv_intel_dp_mode_valid(struct drm_connector *connector,
		    struct drm_display_mode *mode)
{
	struct gma_encoder *encoder = gma_attached_encoder(connector);
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	int max_link_clock = cdv_intel_dp_link_clock(cdv_intel_dp_max_link_bw(encoder));
	int max_lanes = cdv_intel_dp_max_lane_count(encoder);
	struct drm_psb_private *dev_priv = connector->dev->dev_private;

	if (is_edp(encoder) && intel_dp->panel_fixed_mode) {
		if (mode->hdisplay > intel_dp->panel_fixed_mode->hdisplay)
			return MODE_PANEL;
		if (mode->vdisplay > intel_dp->panel_fixed_mode->vdisplay)
			return MODE_PANEL;
	}

	/* only refuse the mode on non eDP since we have seen some weird eDP panels
	   which are outside spec tolerances but somehow work by magic */
	if (!is_edp(encoder) &&
	    (cdv_intel_dp_link_required(mode->clock, dev_priv->edp.bpp)
	     > cdv_intel_dp_max_data_rate(max_link_clock, max_lanes)))
		return MODE_CLOCK_HIGH;

	if (is_edp(encoder)) {
	    if (cdv_intel_dp_link_required(mode->clock, 24)
	     	> cdv_intel_dp_max_data_rate(max_link_clock, max_lanes))
		return MODE_CLOCK_HIGH;
		
	}
	if (mode->clock < 10000)
		return MODE_CLOCK_LOW;

	return MODE_OK;
}