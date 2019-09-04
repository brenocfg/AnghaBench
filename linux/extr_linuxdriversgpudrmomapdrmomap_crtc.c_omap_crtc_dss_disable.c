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
struct omap_drm_private {int dummy; } ;
struct omap_crtc {int /*<<< orphan*/  base; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  omap_crtc_set_enabled (int /*<<< orphan*/ *,int) ; 
 struct omap_crtc** omap_crtcs ; 

__attribute__((used)) static void omap_crtc_dss_disable(struct omap_drm_private *priv,
				  enum omap_channel channel)
{
	struct omap_crtc *omap_crtc = omap_crtcs[channel];

	omap_crtc_set_enabled(&omap_crtc->base, false);
}