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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcs7830_write_phy (struct usbnet*,int,int) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mcs7830_mdio_write(struct net_device *netdev, int phy_id,
				int location, int val)
{
	struct usbnet *dev = netdev_priv(netdev);
	mcs7830_write_phy(dev, location, val);
}