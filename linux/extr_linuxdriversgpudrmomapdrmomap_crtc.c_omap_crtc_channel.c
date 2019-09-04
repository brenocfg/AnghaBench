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
struct omap_crtc {int channel; } ;
struct drm_crtc {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

enum omap_channel omap_crtc_channel(struct drm_crtc *crtc)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	return omap_crtc->channel;
}