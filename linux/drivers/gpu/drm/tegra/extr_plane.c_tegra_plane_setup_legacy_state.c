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
struct tegra_plane_state {int dummy; } ;
struct tegra_plane {int dummy; } ;

/* Variables and functions */
 int tegra_plane_setup_opacity (struct tegra_plane*,struct tegra_plane_state*) ; 
 int tegra_plane_setup_transparency (struct tegra_plane*,struct tegra_plane_state*) ; 

int tegra_plane_setup_legacy_state(struct tegra_plane *tegra,
				   struct tegra_plane_state *state)
{
	int err;

	err = tegra_plane_setup_opacity(tegra, state);
	if (err < 0)
		return err;

	err = tegra_plane_setup_transparency(tegra, state);
	if (err < 0)
		return err;

	return 0;
}