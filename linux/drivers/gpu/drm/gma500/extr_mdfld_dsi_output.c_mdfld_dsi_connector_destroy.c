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
struct mdfld_dsi_pkg_sender {int dummy; } ;
struct mdfld_dsi_connector {struct mdfld_dsi_pkg_sender* pkg_sender; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct mdfld_dsi_connector*) ; 
 struct mdfld_dsi_connector* mdfld_dsi_connector (struct drm_connector*) ; 
 int /*<<< orphan*/  mdfld_dsi_pkg_sender_destroy (struct mdfld_dsi_pkg_sender*) ; 

__attribute__((used)) static void mdfld_dsi_connector_destroy(struct drm_connector *connector)
{
	struct mdfld_dsi_connector *dsi_connector =
					mdfld_dsi_connector(connector);
	struct mdfld_dsi_pkg_sender *sender;

	if (!dsi_connector)
		return;
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	sender = dsi_connector->pkg_sender;
	mdfld_dsi_pkg_sender_destroy(sender);
	kfree(dsi_connector);
}