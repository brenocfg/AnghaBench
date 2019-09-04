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
typedef  int u32 ;
struct mii_bus {struct lan743x_adapter* priv; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MII_ACC ; 
 int /*<<< orphan*/  MAC_MII_DATA ; 
 int /*<<< orphan*/  MAC_MII_READ ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int lan743x_mac_mii_access (int,int,int /*<<< orphan*/ ) ; 
 int lan743x_mac_mii_wait_till_not_busy (struct lan743x_adapter*) ; 

__attribute__((used)) static int lan743x_mdiobus_read(struct mii_bus *bus, int phy_id, int index)
{
	struct lan743x_adapter *adapter = bus->priv;
	u32 val, mii_access;
	int ret;

	/* comfirm MII not busy */
	ret = lan743x_mac_mii_wait_till_not_busy(adapter);
	if (ret < 0)
		return ret;

	/* set the address, index & direction (read from PHY) */
	mii_access = lan743x_mac_mii_access(phy_id, index, MAC_MII_READ);
	lan743x_csr_write(adapter, MAC_MII_ACC, mii_access);
	ret = lan743x_mac_mii_wait_till_not_busy(adapter);
	if (ret < 0)
		return ret;

	val = lan743x_csr_read(adapter, MAC_MII_DATA);
	return (int)(val & 0xFFFF);
}