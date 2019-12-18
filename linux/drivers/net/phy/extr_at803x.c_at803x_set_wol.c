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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {struct net_device* attached_dev; } ;
struct net_device {scalar_t__ dev_addr; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT803X_DEVICE_ADDR ; 
 int /*<<< orphan*/  AT803X_INTR_ENABLE ; 
 int /*<<< orphan*/  AT803X_INTR_ENABLE_WOL ; 
 int /*<<< orphan*/  AT803X_INTR_STATUS ; 
 unsigned int AT803X_LOC_MAC_ADDR_0_15_OFFSET ; 
 unsigned int AT803X_LOC_MAC_ADDR_16_31_OFFSET ; 
 unsigned int AT803X_LOC_MAC_ADDR_32_47_OFFSET ; 
 int EINVAL ; 
 int ENODEV ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  is_valid_ether_addr (int const*) ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,unsigned int,int const) ; 

__attribute__((used)) static int at803x_set_wol(struct phy_device *phydev,
			  struct ethtool_wolinfo *wol)
{
	struct net_device *ndev = phydev->attached_dev;
	const u8 *mac;
	int ret;
	u32 value;
	unsigned int i, offsets[] = {
		AT803X_LOC_MAC_ADDR_32_47_OFFSET,
		AT803X_LOC_MAC_ADDR_16_31_OFFSET,
		AT803X_LOC_MAC_ADDR_0_15_OFFSET,
	};

	if (!ndev)
		return -ENODEV;

	if (wol->wolopts & WAKE_MAGIC) {
		mac = (const u8 *) ndev->dev_addr;

		if (!is_valid_ether_addr(mac))
			return -EINVAL;

		for (i = 0; i < 3; i++)
			phy_write_mmd(phydev, AT803X_DEVICE_ADDR, offsets[i],
				      mac[(i * 2) + 1] | (mac[(i * 2)] << 8));

		value = phy_read(phydev, AT803X_INTR_ENABLE);
		value |= AT803X_INTR_ENABLE_WOL;
		ret = phy_write(phydev, AT803X_INTR_ENABLE, value);
		if (ret)
			return ret;
		value = phy_read(phydev, AT803X_INTR_STATUS);
	} else {
		value = phy_read(phydev, AT803X_INTR_ENABLE);
		value &= (~AT803X_INTR_ENABLE_WOL);
		ret = phy_write(phydev, AT803X_INTR_ENABLE, value);
		if (ret)
			return ret;
		value = phy_read(phydev, AT803X_INTR_STATUS);
	}

	return ret;
}