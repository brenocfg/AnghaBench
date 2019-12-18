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
 int /*<<< orphan*/  tegra_shared_plane_set_owner (struct tegra_plane*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_dc_remove_shared_plane(struct tegra_dc *dc,
					 struct tegra_plane *plane)
{
	tegra_shared_plane_set_owner(plane, NULL);
}