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
typedef  int u32 ;
struct mii_bus {int dummy; } ;
struct b53_device {struct mii_bus* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCM_PSEUDO_PHY_ADDR ; 
 int /*<<< orphan*/  REG_MII_ADDR_WRITE ; 
 scalar_t__ REG_MII_DATA0 ; 
 int b53_mdio_op (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mdiobus_write_nested (struct mii_bus*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int b53_mdio_write32(struct b53_device *dev, u8 page, u8 reg,
			    u32 value)
{
	struct mii_bus *bus = dev->priv;
	unsigned int i;
	u32 temp = value;

	for (i = 0; i < 2; i++) {
		int ret = mdiobus_write_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					       REG_MII_DATA0 + i,
					       temp & 0xffff);
		if (ret)
			return ret;
		temp >>= 16;
	}

	return b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
}