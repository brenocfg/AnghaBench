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
struct tegra_xusb_sata_lane {int dummy; } ;
struct tegra_xusb_lane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tegra_xusb_sata_lane*) ; 
 struct tegra_xusb_sata_lane* to_sata_lane (struct tegra_xusb_lane*) ; 

__attribute__((used)) static void tegra124_sata_lane_remove(struct tegra_xusb_lane *lane)
{
	struct tegra_xusb_sata_lane *sata = to_sata_lane(lane);

	kfree(sata);
}