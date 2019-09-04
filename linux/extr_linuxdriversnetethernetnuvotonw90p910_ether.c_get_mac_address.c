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
struct w90p910_ether {struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_valid_ether_addr (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char**,int) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void get_mac_address(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	struct platform_device *pdev;
	char addr[ETH_ALEN];

	pdev = ether->pdev;

	addr[0] = 0x00;
	addr[1] = 0x02;
	addr[2] = 0xac;
	addr[3] = 0x55;
	addr[4] = 0x88;
	addr[5] = 0xa8;

	if (is_valid_ether_addr(addr))
		memcpy(dev->dev_addr, &addr, ETH_ALEN);
	else
		dev_err(&pdev->dev, "invalid mac address\n");
}