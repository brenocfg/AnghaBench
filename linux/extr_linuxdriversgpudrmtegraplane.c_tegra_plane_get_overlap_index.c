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
struct tegra_plane {unsigned int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static unsigned int tegra_plane_get_overlap_index(struct tegra_plane *plane,
						  struct tegra_plane *other)
{
	unsigned int index = 0, i;

	WARN_ON(plane == other);

	for (i = 0; i < 3; i++) {
		if (i == plane->index)
			continue;

		if (i == other->index)
			break;

		index++;
	}

	return index;
}