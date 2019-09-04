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
struct dsi_connector {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct dsi_connector*) ; 
 struct dsi_connector* to_dsi_connector (struct drm_connector*) ; 

__attribute__((used)) static void dsi_mgr_connector_destroy(struct drm_connector *connector)
{
	struct dsi_connector *dsi_connector = to_dsi_connector(connector);

	DBG("");

	drm_connector_cleanup(connector);

	kfree(dsi_connector);
}