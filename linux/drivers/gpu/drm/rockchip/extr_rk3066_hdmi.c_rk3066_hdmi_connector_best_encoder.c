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
struct drm_encoder {int dummy; } ;
struct rk3066_hdmi {struct drm_encoder encoder; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct rk3066_hdmi* to_rk3066_hdmi (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *
rk3066_hdmi_connector_best_encoder(struct drm_connector *connector)
{
	struct rk3066_hdmi *hdmi = to_rk3066_hdmi(connector);

	return &hdmi->encoder;
}