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
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct omap_crtc {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; } ;
struct dss_lcd_mgr_config {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  (* mgr_set_lcd_config ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dss_lcd_mgr_config const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct omap_crtc** omap_crtcs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dss_lcd_mgr_config const*) ; 

__attribute__((used)) static void omap_crtc_dss_set_lcd_config(struct omap_drm_private *priv,
		enum omap_channel channel,
		const struct dss_lcd_mgr_config *config)
{
	struct omap_crtc *omap_crtc = omap_crtcs[channel];

	DBG("%s", omap_crtc->name);
	priv->dispc_ops->mgr_set_lcd_config(priv->dispc, omap_crtc->channel,
					    config);
}