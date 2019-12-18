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
typedef  int /*<<< orphan*/  u32 ;
struct vsc8531_private {int /*<<< orphan*/  base_addr; } ;
struct TYPE_3__ {TYPE_2__* bus; int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; struct vsc8531_private* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int __mdiobus_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int phy_base_read(struct phy_device *phydev, u32 regnum)
{
	struct vsc8531_private *priv = phydev->priv;

	if (unlikely(!mutex_is_locked(&phydev->mdio.bus->mdio_lock))) {
		dev_err(&phydev->mdio.dev, "MDIO bus lock not held!\n");
		dump_stack();
	}

	return __mdiobus_read(phydev->mdio.bus, priv->base_addr, regnum);
}