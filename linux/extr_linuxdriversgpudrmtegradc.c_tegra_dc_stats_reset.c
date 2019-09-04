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
struct tegra_dc_stats {scalar_t__ overflow; scalar_t__ underflow; scalar_t__ vblank; scalar_t__ frames; } ;

/* Variables and functions */

__attribute__((used)) static void tegra_dc_stats_reset(struct tegra_dc_stats *stats)
{
	stats->frames = 0;
	stats->vblank = 0;
	stats->underflow = 0;
	stats->overflow = 0;
}