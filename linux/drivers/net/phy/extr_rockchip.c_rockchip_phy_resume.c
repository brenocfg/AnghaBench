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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  genphy_resume (struct phy_device*) ; 
 int rockchip_integrated_phy_config_init (struct phy_device*) ; 

__attribute__((used)) static int rockchip_phy_resume(struct phy_device *phydev)
{
	genphy_resume(phydev);

	return rockchip_integrated_phy_config_init(phydev);
}