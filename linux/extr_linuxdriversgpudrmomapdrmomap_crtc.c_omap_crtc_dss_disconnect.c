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
struct omap_dss_device {int dispc_channel_connected; } ;
struct omap_drm_private {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/ ** omap_crtc_output ; 

__attribute__((used)) static void omap_crtc_dss_disconnect(struct omap_drm_private *priv,
		enum omap_channel channel,
		struct omap_dss_device *dst)
{
	omap_crtc_output[channel] = NULL;
	dst->dispc_channel_connected = false;
}