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
struct radeon_connector {struct drm_connector* con_priv; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_connector_free_edid (struct drm_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static void radeon_connector_destroy(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);

	radeon_connector_free_edid(connector);
	kfree(radeon_connector->con_priv);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}