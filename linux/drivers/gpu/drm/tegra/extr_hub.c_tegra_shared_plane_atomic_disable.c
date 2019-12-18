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
struct tegra_plane {struct tegra_dc* dc; } ;
struct tegra_dc {int /*<<< orphan*/  dev; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_WIN_WIN_OPTIONS ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIN_ENABLE ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_remove_shared_plane (struct tegra_dc*,struct tegra_plane*) ; 
 int /*<<< orphan*/  tegra_plane_readl (struct tegra_plane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_plane_writel (struct tegra_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 

__attribute__((used)) static void tegra_shared_plane_atomic_disable(struct drm_plane *plane,
					      struct drm_plane_state *old_state)
{
	struct tegra_plane *p = to_tegra_plane(plane);
	struct tegra_dc *dc;
	u32 value;

	/* rien ne va plus */
	if (!old_state || !old_state->crtc)
		return;

	dc = to_tegra_dc(old_state->crtc);

	/*
	 * XXX Legacy helpers seem to sometimes call ->atomic_disable() even
	 * on planes that are already disabled. Make sure we fallback to the
	 * head for this particular state instead of crashing.
	 */
	if (WARN_ON(p->dc == NULL))
		p->dc = dc;

	pm_runtime_get_sync(dc->dev);

	value = tegra_plane_readl(p, DC_WIN_WIN_OPTIONS);
	value &= ~WIN_ENABLE;
	tegra_plane_writel(p, value, DC_WIN_WIN_OPTIONS);

	tegra_dc_remove_shared_plane(dc, p);

	pm_runtime_put(dc->dev);
}