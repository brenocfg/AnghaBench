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
struct seq_file {int dummy; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int /*<<< orphan*/  aux; int /*<<< orphan*/  downstream_ports; int /*<<< orphan*/ * dpcd; int /*<<< orphan*/  has_audio; } ;
struct TYPE_4__ {scalar_t__ shim; } ;
struct TYPE_3__ {scalar_t__ connector_type; } ;
struct intel_connector {TYPE_2__ hdcp; int /*<<< orphan*/  panel; TYPE_1__ base; struct intel_encoder* encoder; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int /*<<< orphan*/  drm_dp_downstream_debug (struct seq_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdcp_info (struct seq_file*,struct intel_connector*) ; 
 int /*<<< orphan*/  intel_panel_info (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_info(struct seq_file *m,
			  struct intel_connector *intel_connector)
{
	struct intel_encoder *intel_encoder = intel_connector->encoder;
	struct intel_dp *intel_dp = enc_to_intel_dp(&intel_encoder->base);

	seq_printf(m, "\tDPCD rev: %x\n", intel_dp->dpcd[DP_DPCD_REV]);
	seq_printf(m, "\taudio support: %s\n", yesno(intel_dp->has_audio));
	if (intel_connector->base.connector_type == DRM_MODE_CONNECTOR_eDP)
		intel_panel_info(m, &intel_connector->panel);

	drm_dp_downstream_debug(m, intel_dp->dpcd, intel_dp->downstream_ports,
				&intel_dp->aux);
	if (intel_connector->hdcp.shim) {
		seq_puts(m, "\tHDCP version: ");
		intel_hdcp_info(m, intel_connector);
	}
}