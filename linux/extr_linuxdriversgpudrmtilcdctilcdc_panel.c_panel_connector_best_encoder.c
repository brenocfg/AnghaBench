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
struct panel_connector {struct drm_encoder* encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct panel_connector* to_panel_connector (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *panel_connector_best_encoder(
		struct drm_connector *connector)
{
	struct panel_connector *panel_connector = to_panel_connector(connector);
	return panel_connector->encoder;
}