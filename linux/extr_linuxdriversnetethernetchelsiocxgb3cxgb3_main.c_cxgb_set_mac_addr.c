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
struct port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  mac; struct adapter* adapter; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  LAN_MAC_IDX ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ offload_running (struct adapter*) ; 
 int /*<<< orphan*/  t3_mac_set_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smt_entry (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb_set_mac_addr(struct net_device *dev, void *p)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	t3_mac_set_address(&pi->mac, LAN_MAC_IDX, dev->dev_addr);
	if (offload_running(adapter))
		write_smt_entry(adapter, pi->port_id);
	return 0;
}