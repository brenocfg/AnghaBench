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
struct TYPE_5__ {int max_tmds_clock; } ;
struct intel_hdmi {int /*<<< orphan*/  has_hdmi_sink; TYPE_2__ dp_dual_mode; struct intel_connector* attached_connector; } ;
struct intel_encoder {int dummy; } ;
struct drm_display_info {int max_tmds_clock; } ;
struct TYPE_4__ {struct drm_display_info display_info; } ;
struct intel_connector {TYPE_1__ base; } ;
struct TYPE_6__ {struct intel_encoder base; } ;

/* Variables and functions */
 TYPE_3__* hdmi_to_dig_port (struct intel_hdmi*) ; 
 int intel_hdmi_source_max_tmds_clock (struct intel_encoder*) ; 
 int min (int,int) ; 

__attribute__((used)) static int hdmi_port_clock_limit(struct intel_hdmi *hdmi,
				 bool respect_downstream_limits,
				 bool force_dvi)
{
	struct intel_encoder *encoder = &hdmi_to_dig_port(hdmi)->base;
	int max_tmds_clock = intel_hdmi_source_max_tmds_clock(encoder);

	if (respect_downstream_limits) {
		struct intel_connector *connector = hdmi->attached_connector;
		const struct drm_display_info *info = &connector->base.display_info;

		if (hdmi->dp_dual_mode.max_tmds_clock)
			max_tmds_clock = min(max_tmds_clock,
					     hdmi->dp_dual_mode.max_tmds_clock);

		if (info->max_tmds_clock)
			max_tmds_clock = min(max_tmds_clock,
					     info->max_tmds_clock);
		else if (!hdmi->has_hdmi_sink || force_dvi)
			max_tmds_clock = min(max_tmds_clock, 165000);
	}

	return max_tmds_clock;
}