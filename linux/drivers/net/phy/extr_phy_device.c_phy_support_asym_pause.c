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
struct phy_device {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_copy_pause_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phy_support_asym_pause(struct phy_device *phydev)
{
	phy_copy_pause_bits(phydev->advertising, phydev->supported);
}