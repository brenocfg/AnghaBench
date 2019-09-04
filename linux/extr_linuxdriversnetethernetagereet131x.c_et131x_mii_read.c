#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct phy_device {TYPE_2__ mdio; } ;
struct et131x_adapter {TYPE_1__* netdev; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;

/* Variables and functions */
 int EIO ; 
 int et131x_phy_mii_read (struct et131x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et131x_mii_read(struct et131x_adapter *adapter, u8 reg, u16 *value)
{
	struct phy_device *phydev = adapter->netdev->phydev;

	if (!phydev)
		return -EIO;

	return et131x_phy_mii_read(adapter, phydev->mdio.addr, reg, value);
}