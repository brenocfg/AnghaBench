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
typedef  void* u8 ;
typedef  int u32 ;
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;
struct net_device {void** dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRH ; 
 int /*<<< orphan*/  ADDRL ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 scalar_t__ is_valid_ether_addr (void**) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_set_mac_address (struct net_device*) ; 

__attribute__((used)) static void smsc9420_check_mac_address(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);

	/* Check if mac address has been specified when bringing interface up */
	if (is_valid_ether_addr(dev->dev_addr)) {
		smsc9420_set_mac_address(dev);
		netif_dbg(pd, probe, pd->dev,
			  "MAC Address is specified by configuration\n");
	} else {
		/* Try reading mac address from device. if EEPROM is present
		 * it will already have been set */
		u32 mac_high16 = smsc9420_reg_read(pd, ADDRH);
		u32 mac_low32 = smsc9420_reg_read(pd, ADDRL);
		dev->dev_addr[0] = (u8)(mac_low32);
		dev->dev_addr[1] = (u8)(mac_low32 >> 8);
		dev->dev_addr[2] = (u8)(mac_low32 >> 16);
		dev->dev_addr[3] = (u8)(mac_low32 >> 24);
		dev->dev_addr[4] = (u8)(mac_high16);
		dev->dev_addr[5] = (u8)(mac_high16 >> 8);

		if (is_valid_ether_addr(dev->dev_addr)) {
			/* eeprom values are valid  so use them */
			netif_dbg(pd, probe, pd->dev,
				  "Mac Address is read from EEPROM\n");
		} else {
			/* eeprom values are invalid, generate random MAC */
			eth_hw_addr_random(dev);
			smsc9420_set_mac_address(dev);
			netif_dbg(pd, probe, pd->dev,
				  "MAC Address is set to random\n");
		}
	}
}