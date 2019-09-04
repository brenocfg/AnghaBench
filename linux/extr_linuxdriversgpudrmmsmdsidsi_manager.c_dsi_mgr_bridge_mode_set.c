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
struct msm_dsi {struct mipi_dsi_host* host; } ;
struct mipi_dsi_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_display_mode {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hdisplay; int /*<<< orphan*/  clock; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IS_DUAL_DSI () ; 
 int /*<<< orphan*/  IS_MASTER_DSI_LINK (int) ; 
 int dsi_mgr_bridge_get_id (struct drm_bridge*) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 struct msm_dsi* dsi_mgr_get_other_dsi (int) ; 
 int /*<<< orphan*/  msm_dsi_host_set_display_mode (struct mipi_dsi_host*,struct drm_display_mode*) ; 

__attribute__((used)) static void dsi_mgr_bridge_mode_set(struct drm_bridge *bridge,
		struct drm_display_mode *mode,
		struct drm_display_mode *adjusted_mode)
{
	int id = dsi_mgr_bridge_get_id(bridge);
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	struct mipi_dsi_host *host = msm_dsi->host;
	bool is_dual_dsi = IS_DUAL_DSI();

	DBG("set mode: %d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x",
			mode->base.id, mode->name,
			mode->vrefresh, mode->clock,
			mode->hdisplay, mode->hsync_start,
			mode->hsync_end, mode->htotal,
			mode->vdisplay, mode->vsync_start,
			mode->vsync_end, mode->vtotal,
			mode->type, mode->flags);

	if (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		return;

	msm_dsi_host_set_display_mode(host, adjusted_mode);
	if (is_dual_dsi && other_dsi)
		msm_dsi_host_set_display_mode(other_dsi->host, adjusted_mode);
}