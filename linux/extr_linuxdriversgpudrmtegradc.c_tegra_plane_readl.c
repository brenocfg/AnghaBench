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
struct tegra_plane {int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_dc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_plane_offset (struct tegra_plane*,unsigned int) ; 

__attribute__((used)) static inline u32 tegra_plane_readl(struct tegra_plane *plane,
				    unsigned int offset)
{
	return tegra_dc_readl(plane->dc, tegra_plane_offset(plane, offset));
}