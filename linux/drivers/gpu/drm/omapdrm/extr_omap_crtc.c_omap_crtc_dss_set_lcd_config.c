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
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_2__* dispc_ops; TYPE_1__** channels; } ;
struct omap_crtc {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; } ;
struct dss_lcd_mgr_config {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_4__ {int /*<<< orphan*/  (* mgr_set_lcd_config ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dss_lcd_mgr_config const*) ;} ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dss_lcd_mgr_config const*) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void omap_crtc_dss_set_lcd_config(struct omap_drm_private *priv,
		enum omap_channel channel,
		const struct dss_lcd_mgr_config *config)
{
	struct drm_crtc *crtc = priv->channels[channel]->crtc;
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);

	DBG("%s", omap_crtc->name);
	priv->dispc_ops->mgr_set_lcd_config(priv->dispc, omap_crtc->channel,
					    config);
}