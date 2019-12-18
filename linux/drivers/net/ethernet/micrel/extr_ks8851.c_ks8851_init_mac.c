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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ks8851_net {int rc_ccr; struct net_device* netdev; TYPE_2__* spidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int CCR_EEPROM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_read_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  ks8851_write_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_mac_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks8851_init_mac(struct ks8851_net *ks)
{
	struct net_device *dev = ks->netdev;
	const u8 *mac_addr;

	mac_addr = of_get_mac_address(ks->spidev->dev.of_node);
	if (!IS_ERR(mac_addr)) {
		ether_addr_copy(dev->dev_addr, mac_addr);
		ks8851_write_mac_addr(dev);
		return;
	}

	if (ks->rc_ccr & CCR_EEPROM) {
		ks8851_read_mac_addr(dev);
		if (is_valid_ether_addr(dev->dev_addr))
			return;

		netdev_err(ks->netdev, "invalid mac address read %pM\n",
				dev->dev_addr);
	}

	eth_hw_addr_random(dev);
	ks8851_write_mac_addr(dev);
}