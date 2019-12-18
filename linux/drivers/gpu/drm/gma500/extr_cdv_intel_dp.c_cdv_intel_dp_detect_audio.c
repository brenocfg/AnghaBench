#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct cdv_intel_dp {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_off (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_on (struct gma_encoder*) ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int is_edp (struct gma_encoder*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static bool
cdv_intel_dp_detect_audio(struct drm_connector *connector)
{
	struct gma_encoder *encoder = gma_attached_encoder(connector);
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	struct edid *edid;
	bool has_audio = false;
	int edp = is_edp(encoder);

	if (edp)
		cdv_intel_edp_panel_vdd_on(encoder);

	edid = drm_get_edid(connector, &intel_dp->adapter);
	if (edid) {
		has_audio = drm_detect_monitor_audio(edid);
		kfree(edid);
	}
	if (edp)
		cdv_intel_edp_panel_vdd_off(encoder);

	return has_audio;
}