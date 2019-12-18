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
struct port_info {int /*<<< orphan*/  xact_addr_filt; int /*<<< orphan*/  viid; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int cxgb4vf_change_mac (struct port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cxgb4vf_set_mac_addr(struct net_device *dev, void *_addr)
{
	int ret;
	struct sockaddr *addr = _addr;
	struct port_info *pi = netdev_priv(dev);

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	ret = cxgb4vf_change_mac(pi, pi->viid, &pi->xact_addr_filt,
				 addr->sa_data, true);
	if (ret < 0)
		return ret;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	return 0;
}