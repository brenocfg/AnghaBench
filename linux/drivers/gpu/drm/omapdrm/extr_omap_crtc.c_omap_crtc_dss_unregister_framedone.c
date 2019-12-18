#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_drm_private {TYPE_1__** channels; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct omap_crtc {void (* framedone_handler ) (void*) ;void* framedone_handler_data; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void omap_crtc_dss_unregister_framedone(
		struct omap_drm_private *priv, enum omap_channel channel,
		void (*handler)(void *), void *data)
{
	struct drm_crtc *crtc = priv->channels[channel]->crtc;
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	struct drm_device *dev = omap_crtc->base.dev;

	dev_dbg(dev->dev, "unregister framedone %s", omap_crtc->name);

	WARN_ON(omap_crtc->framedone_handler != handler);
	WARN_ON(omap_crtc->framedone_handler_data != data);

	omap_crtc->framedone_handler = NULL;
	omap_crtc->framedone_handler_data = NULL;
}