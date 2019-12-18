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
struct sti_dvo_connector {struct sti_dvo* dvo; } ;
struct sti_dvo {int /*<<< orphan*/ * panel; int /*<<< orphan*/  panel_node; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  drm_panel_attach (int /*<<< orphan*/ *,struct drm_connector*) ; 
 int /*<<< orphan*/ * of_drm_find_panel (int /*<<< orphan*/ ) ; 
 struct sti_dvo_connector* to_sti_dvo_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
sti_dvo_connector_detect(struct drm_connector *connector, bool force)
{
	struct sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	struct sti_dvo *dvo = dvo_connector->dvo;

	DRM_DEBUG_DRIVER("\n");

	if (!dvo->panel) {
		dvo->panel = of_drm_find_panel(dvo->panel_node);
		if (IS_ERR(dvo->panel))
			dvo->panel = NULL;
		else
			drm_panel_attach(dvo->panel, connector);
	}

	if (dvo->panel)
		return connector_status_connected;

	return connector_status_disconnected;
}