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
struct omap_overlay_manager_info {int default_color; int trans_enabled; int partial_alpha_enabled; int cpr_enable; } ;
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct omap_crtc {int /*<<< orphan*/  channel; } ;
struct drm_crtc {TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {struct omap_drm_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mgr_setup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_overlay_manager_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct omap_overlay_manager_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_overlay_manager_info*) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void omap_crtc_write_crtc_properties(struct drm_crtc *crtc)
{
	struct omap_drm_private *priv = crtc->dev->dev_private;
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	struct omap_overlay_manager_info info;

	memset(&info, 0, sizeof(info));

	info.default_color = 0x000000;
	info.trans_enabled = false;
	info.partial_alpha_enabled = false;
	info.cpr_enable = false;

	priv->dispc_ops->mgr_setup(priv->dispc, omap_crtc->channel, &info);
}