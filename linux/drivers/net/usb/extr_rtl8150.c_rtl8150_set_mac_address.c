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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; int addr_len; } ;
typedef  int /*<<< orphan*/  rtl8150_t ;

/* Variables and functions */
 scalar_t__ CR ; 
 int EBUSY ; 
 scalar_t__ IDR ; 
 scalar_t__ IDR_EEPROM ; 
 int /*<<< orphan*/  get_registers (int /*<<< orphan*/ *,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_registers (int /*<<< orphan*/ *,scalar_t__,int,int*) ; 

__attribute__((used)) static int rtl8150_set_mac_address(struct net_device *netdev, void *p)
{
	struct sockaddr *addr = p;
	rtl8150_t *dev = netdev_priv(netdev);

	if (netif_running(netdev))
		return -EBUSY;

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	netdev_dbg(netdev, "Setting MAC address to %pM\n", netdev->dev_addr);
	/* Set the IDR registers. */
	set_registers(dev, IDR, netdev->addr_len, netdev->dev_addr);
#ifdef EEPROM_WRITE
	{
	int i;
	u8 cr;
	/* Get the CR contents. */
	get_registers(dev, CR, 1, &cr);
	/* Set the WEPROM bit (eeprom write enable). */
	cr |= 0x20;
	set_registers(dev, CR, 1, &cr);
	/* Write the MAC address into eeprom. Eeprom writes must be word-sized,
	   so we need to split them up. */
	for (i = 0; i * 2 < netdev->addr_len; i++) {
		set_registers(dev, IDR_EEPROM + (i * 2), 2,
		netdev->dev_addr + (i * 2));
	}
	/* Clear the WEPROM bit (preventing accidental eeprom writes). */
	cr &= 0xdf;
	set_registers(dev, CR, 1, &cr);
	}
#endif
	return 0;
}