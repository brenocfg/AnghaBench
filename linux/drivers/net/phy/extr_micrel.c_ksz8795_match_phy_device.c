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
 int /*<<< orphan*/  PHY_ID_KSZ87XX ; 
 int ksz8051_ksz8795_match_phy_device (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz8795_match_phy_device(struct phy_device *phydev)
{
	return ksz8051_ksz8795_match_phy_device(phydev, PHY_ID_KSZ87XX);
}