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
struct sockaddr_ax25 {int /*<<< orphan*/  sax25_call; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 

__attribute__((used)) static int sp_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr_ax25 *sa = addr;

	netif_tx_lock_bh(dev);
	netif_addr_lock(dev);
	memcpy(dev->dev_addr, &sa->sax25_call, AX25_ADDR_LEN);
	netif_addr_unlock(dev);
	netif_tx_unlock_bh(dev);

	return 0;
}