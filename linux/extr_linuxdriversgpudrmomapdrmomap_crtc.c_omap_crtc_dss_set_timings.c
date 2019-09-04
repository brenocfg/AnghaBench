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
struct videomode {int dummy; } ;
struct omap_drm_private {int dummy; } ;
struct omap_crtc {struct videomode vm; int /*<<< orphan*/  name; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct omap_crtc** omap_crtcs ; 

__attribute__((used)) static void omap_crtc_dss_set_timings(struct omap_drm_private *priv,
		enum omap_channel channel,
		const struct videomode *vm)
{
	struct omap_crtc *omap_crtc = omap_crtcs[channel];
	DBG("%s", omap_crtc->name);
	omap_crtc->vm = *vm;
}