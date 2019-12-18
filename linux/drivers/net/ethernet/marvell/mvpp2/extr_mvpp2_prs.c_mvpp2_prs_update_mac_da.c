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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  const* dev_addr; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mvpp2_prs_mac_da_accept (struct mvpp2_port*,int /*<<< orphan*/  const*,int) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

int mvpp2_prs_update_mac_da(struct net_device *dev, const u8 *da)
{
	struct mvpp2_port *port = netdev_priv(dev);
	int err;

	/* Remove old parser entry */
	err = mvpp2_prs_mac_da_accept(port, dev->dev_addr, false);
	if (err)
		return err;

	/* Add new parser entry */
	err = mvpp2_prs_mac_da_accept(port, da, true);
	if (err)
		return err;

	/* Set addr in the device */
	ether_addr_copy(dev->dev_addr, da);

	return 0;
}