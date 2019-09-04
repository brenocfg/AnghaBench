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
struct cdv_intel_dp {int has_audio; scalar_t__ force_audio; int /*<<< orphan*/  adapter; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int cdv_dp_detect (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_off (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_on (struct gma_encoder*) ; 
 int connector_status_connected ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int is_edp (struct gma_encoder*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static enum drm_connector_status
cdv_intel_dp_detect(struct drm_connector *connector, bool force)
{
	struct gma_encoder *encoder = gma_attached_encoder(connector);
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	enum drm_connector_status status;
	struct edid *edid = NULL;
	int edp = is_edp(encoder);

	intel_dp->has_audio = false;

	if (edp)
		cdv_intel_edp_panel_vdd_on(encoder);
	status = cdv_dp_detect(encoder);
	if (status != connector_status_connected) {
		if (edp)
			cdv_intel_edp_panel_vdd_off(encoder);
		return status;
        }

	if (intel_dp->force_audio) {
		intel_dp->has_audio = intel_dp->force_audio > 0;
	} else {
		edid = drm_get_edid(connector, &intel_dp->adapter);
		if (edid) {
			intel_dp->has_audio = drm_detect_monitor_audio(edid);
			kfree(edid);
		}
	}
	if (edp)
		cdv_intel_edp_panel_vdd_off(encoder);

	return connector_status_connected;
}