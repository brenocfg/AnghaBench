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
struct tegra_plane {int dummy; } ;
struct tegra_dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_WIN_CORE_WINDOWGROUP_SET_CONTROL ; 
 unsigned int OWNER_MASK ; 
 unsigned int tegra_dc_readl (struct tegra_dc*,unsigned int) ; 
 unsigned int tegra_plane_offset (struct tegra_plane*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tegra_shared_plane_get_owner(struct tegra_plane *plane, struct tegra_dc *dc)
{
	unsigned int offset =
		tegra_plane_offset(plane, DC_WIN_CORE_WINDOWGROUP_SET_CONTROL);

	return tegra_dc_readl(dc, offset) & OWNER_MASK;
}