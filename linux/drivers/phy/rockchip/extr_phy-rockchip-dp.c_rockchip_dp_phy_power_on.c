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
struct phy {int dummy; } ;

/* Variables and functions */
 int rockchip_set_phy_state (struct phy*,int) ; 

__attribute__((used)) static int rockchip_dp_phy_power_on(struct phy *phy)
{
	return rockchip_set_phy_state(phy, true);
}