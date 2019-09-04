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
struct tegra_plane {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_WIN_WIN_OPTIONS ; 
 int /*<<< orphan*/  WIN_ENABLE ; 
 int /*<<< orphan*/  tegra_plane_readl (struct tegra_plane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_plane_writel (struct tegra_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 

__attribute__((used)) static void tegra_plane_atomic_disable(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct tegra_plane *p = to_tegra_plane(plane);
	u32 value;

	/* rien ne va plus */
	if (!old_state || !old_state->crtc)
		return;

	value = tegra_plane_readl(p, DC_WIN_WIN_OPTIONS);
	value &= ~WIN_ENABLE;
	tegra_plane_writel(p, value, DC_WIN_WIN_OPTIONS);
}