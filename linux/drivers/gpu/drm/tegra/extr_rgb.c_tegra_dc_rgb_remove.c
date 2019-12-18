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
struct tegra_dc {int /*<<< orphan*/ * rgb; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_output_remove (int /*<<< orphan*/ *) ; 

int tegra_dc_rgb_remove(struct tegra_dc *dc)
{
	if (!dc->rgb)
		return 0;

	tegra_output_remove(dc->rgb);
	dc->rgb = NULL;

	return 0;
}