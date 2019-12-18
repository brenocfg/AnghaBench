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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ETH_ALEN ; 
 scalar_t__ PP_IA ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int*) ; 
 int /*<<< orphan*/  writereg (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static int set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *saddr = addr;
	int i;

	if (!is_valid_ether_addr(saddr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, saddr->sa_data, ETH_ALEN);
	netdev_info(dev, "Setting MAC address to %pM\n", dev->dev_addr);

	/* set the Ethernet address */
	for (i=0; i < ETH_ALEN/2; i++)
		writereg(dev, PP_IA+i*2, dev->dev_addr[i*2] | (dev->dev_addr[i*2+1] << 8));

	return 0;
}