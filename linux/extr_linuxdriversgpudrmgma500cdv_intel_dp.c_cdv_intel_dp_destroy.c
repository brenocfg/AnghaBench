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
struct drm_connector {int dummy; } ;
struct cdv_intel_dp {int /*<<< orphan*/  adapter; struct drm_connector* panel_fixed_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 scalar_t__ is_edp (struct gma_encoder*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 

__attribute__((used)) static void
cdv_intel_dp_destroy(struct drm_connector *connector)
{
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct cdv_intel_dp *intel_dp = gma_encoder->dev_priv;

	if (is_edp(gma_encoder)) {
	/*	cdv_intel_panel_destroy_backlight(connector->dev); */
		kfree(intel_dp->panel_fixed_mode);
		intel_dp->panel_fixed_mode = NULL;
	}
	i2c_del_adapter(&intel_dp->adapter);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}