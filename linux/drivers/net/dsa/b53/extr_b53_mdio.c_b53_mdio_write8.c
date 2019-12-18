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
typedef  int /*<<< orphan*/  u8 ;
struct mii_bus {int dummy; } ;
struct b53_device {struct mii_bus* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCM_PSEUDO_PHY_ADDR ; 
 int /*<<< orphan*/  REG_MII_ADDR_WRITE ; 
 int /*<<< orphan*/  REG_MII_DATA0 ; 
 int b53_mdio_op (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mdiobus_write_nested (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b53_mdio_write8(struct b53_device *dev, u8 page, u8 reg, u8 value)
{
	struct mii_bus *bus = dev->priv;
	int ret;

	ret = mdiobus_write_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				   REG_MII_DATA0, value);
	if (ret)
		return ret;

	return b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
}