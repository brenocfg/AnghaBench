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
struct tegra_plane {int /*<<< orphan*/  index; struct tegra_dc* dc; } ;
struct tegra_dc {int /*<<< orphan*/  pipe; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_shared_plane_get_owner (struct tegra_plane*,struct tegra_dc*) ; 

__attribute__((used)) static bool tegra_dc_owns_shared_plane(struct tegra_dc *dc,
				       struct tegra_plane *plane)
{
	struct device *dev = dc->dev;

	if (tegra_shared_plane_get_owner(plane, dc) == dc->pipe) {
		if (plane->dc == dc)
			return true;

		dev_WARN(dev, "head %u owns window %u but is not attached\n",
			 dc->pipe, plane->index);
	}

	return false;
}