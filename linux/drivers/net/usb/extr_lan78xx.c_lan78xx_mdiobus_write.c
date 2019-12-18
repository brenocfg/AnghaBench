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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct mii_bus {struct lan78xx_net* priv; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; int /*<<< orphan*/  phy_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ACC ; 
 int /*<<< orphan*/  MII_DATA ; 
 int /*<<< orphan*/  MII_WRITE ; 
 int lan78xx_phy_wait_not_busy (struct lan78xx_net*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mii_access (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_mdiobus_write(struct mii_bus *bus, int phy_id, int idx,
				 u16 regval)
{
	struct lan78xx_net *dev = bus->priv;
	u32 val, addr;
	int ret;

	ret = usb_autopm_get_interface(dev->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = lan78xx_phy_wait_not_busy(dev);
	if (ret < 0)
		goto done;

	val = (u32)regval;
	ret = lan78xx_write_reg(dev, MII_DATA, val);

	/* set the address, index & direction (write to PHY) */
	addr = mii_access(phy_id, idx, MII_WRITE);
	ret = lan78xx_write_reg(dev, MII_ACC, addr);

	ret = lan78xx_phy_wait_not_busy(dev);
	if (ret < 0)
		goto done;

done:
	mutex_unlock(&dev->phy_mutex);
	usb_autopm_put_interface(dev->intf);
	return 0;
}