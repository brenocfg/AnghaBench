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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_dc {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_ENABLE ; 
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_cursor_atomic_disable(struct drm_plane *plane,
					struct drm_plane_state *old_state)
{
	struct tegra_dc *dc;
	u32 value;

	/* rien ne va plus */
	if (!old_state || !old_state->crtc)
		return;

	dc = to_tegra_dc(old_state->crtc);

	value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value &= ~CURSOR_ENABLE;
	tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);
}