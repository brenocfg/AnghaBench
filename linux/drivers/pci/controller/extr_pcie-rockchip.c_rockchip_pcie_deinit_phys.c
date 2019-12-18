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
struct rockchip_pcie {int lanes_map; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAX_LANE_NUM ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

void rockchip_pcie_deinit_phys(struct rockchip_pcie *rockchip)
{
	int i;

	for (i = 0; i < MAX_LANE_NUM; i++) {
		/* inactive lanes are already powered off */
		if (rockchip->lanes_map & BIT(i))
			phy_power_off(rockchip->phys[i]);
		phy_exit(rockchip->phys[i]);
	}
}