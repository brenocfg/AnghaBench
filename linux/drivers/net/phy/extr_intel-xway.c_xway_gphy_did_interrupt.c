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
 int XWAY_MDIO_INIT_MASK ; 
 int /*<<< orphan*/  XWAY_MDIO_ISTAT ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xway_gphy_did_interrupt(struct phy_device *phydev)
{
	int reg;

	reg = phy_read(phydev, XWAY_MDIO_ISTAT);
	return reg & XWAY_MDIO_INIT_MASK;
}