#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_3__* net; TYPE_2__* udev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAC_OFFSET ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_3__*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * of_get_mac_address (int /*<<< orphan*/ ) ; 
 scalar_t__ smsc75xx_read_eeprom (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsc75xx_init_mac_address(struct usbnet *dev)
{
	const u8 *mac_addr;

	/* maybe the boot loader passed the MAC address in devicetree */
	mac_addr = of_get_mac_address(dev->udev->dev.of_node);
	if (!IS_ERR(mac_addr)) {
		ether_addr_copy(dev->net->dev_addr, mac_addr);
		return;
	}

	/* try reading mac address from EEPROM */
	if (smsc75xx_read_eeprom(dev, EEPROM_MAC_OFFSET, ETH_ALEN,
			dev->net->dev_addr) == 0) {
		if (is_valid_ether_addr(dev->net->dev_addr)) {
			/* eeprom values are valid so use them */
			netif_dbg(dev, ifup, dev->net,
				  "MAC address read from EEPROM\n");
			return;
		}
	}

	/* no useful static MAC address found. generate a random one */
	eth_hw_addr_random(dev->net);
	netif_dbg(dev, ifup, dev->net, "MAC address set to eth_random_addr\n");
}