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
typedef  int u32 ;
struct tegra_dc_state {int planes; } ;
struct tegra_dc {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CMD_STATE_CONTROL ; 
 int GENERAL_ACT_REQ ; 
 int GENERAL_UPDATE ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 
 struct tegra_dc_state* to_dc_state (int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (struct drm_crtc*) ; 

__attribute__((used)) static void tegra_crtc_atomic_flush(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_crtc_state)
{
	struct tegra_dc_state *state = to_dc_state(crtc->state);
	struct tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	value = state->planes << 8 | GENERAL_UPDATE;
	tegra_dc_writel(dc, value, DC_CMD_STATE_CONTROL);
	value = tegra_dc_readl(dc, DC_CMD_STATE_CONTROL);

	value = state->planes | GENERAL_ACT_REQ;
	tegra_dc_writel(dc, value, DC_CMD_STATE_CONTROL);
	value = tegra_dc_readl(dc, DC_CMD_STATE_CONTROL);
}