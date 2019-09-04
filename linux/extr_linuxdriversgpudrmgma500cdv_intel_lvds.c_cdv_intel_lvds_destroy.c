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
struct gma_encoder {int /*<<< orphan*/  i2c_bus; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 int /*<<< orphan*/  psb_intel_i2c_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdv_intel_lvds_destroy(struct drm_connector *connector)
{
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);

	psb_intel_i2c_destroy(gma_encoder->i2c_bus);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}