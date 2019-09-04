#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_connector_state {struct drm_connector* connector; } ;
struct TYPE_2__ {int bpc; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */

__attribute__((used)) static bool hdmi_sink_is_deep_color(const struct drm_connector_state *conn_state)
{
	struct drm_connector *connector = conn_state->connector;

	/*
	 * HDMI cloning is only supported on g4x which doesn't
	 * support deep color or GCP infoframes anyway so no
	 * need to worry about multiple HDMI sinks here.
	 */

	return connector->display_info.bpc > 8;
}