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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; } ;
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 int /*<<< orphan*/  MAF_HI (int /*<<< orphan*/ ) ; 
 int MAF_HI_VALID_ ; 
 int /*<<< orphan*/  MAF_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_ADDRH ; 
 int /*<<< orphan*/  RX_ADDRL ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int lan78xx_set_mac_addr(struct net_device *netdev, void *p)
{
	struct lan78xx_net *dev = netdev_priv(netdev);
	struct sockaddr *addr = p;
	u32 addr_lo, addr_hi;
	int ret;

	if (netif_running(netdev))
		return -EBUSY;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	ether_addr_copy(netdev->dev_addr, addr->sa_data);

	addr_lo = netdev->dev_addr[0] |
		  netdev->dev_addr[1] << 8 |
		  netdev->dev_addr[2] << 16 |
		  netdev->dev_addr[3] << 24;
	addr_hi = netdev->dev_addr[4] |
		  netdev->dev_addr[5] << 8;

	ret = lan78xx_write_reg(dev, RX_ADDRL, addr_lo);
	ret = lan78xx_write_reg(dev, RX_ADDRH, addr_hi);

	/* Added to support MAC address changes */
	ret = lan78xx_write_reg(dev, MAF_LO(0), addr_lo);
	ret = lan78xx_write_reg(dev, MAF_HI(0), addr_hi | MAF_HI_VALID_);

	return 0;
}