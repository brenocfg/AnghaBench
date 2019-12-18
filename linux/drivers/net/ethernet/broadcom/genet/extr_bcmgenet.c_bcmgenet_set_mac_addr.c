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
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bcmgenet_set_mac_addr(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;

	/* Setting the MAC address at the hardware level is not possible
	 * without disabling the UniMAC RX/TX enable bits.
	 */
	if (netif_running(dev))
		return -EBUSY;

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	return 0;
}