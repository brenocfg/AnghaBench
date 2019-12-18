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
struct port_info {int /*<<< orphan*/  adapter; int /*<<< orphan*/  xact_addr_filt; int /*<<< orphan*/  viid; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int cxgb4vf_change_mac (struct port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4vf_enable_pi (int /*<<< orphan*/ ,struct port_info*,int,int) ; 
 int t4vf_set_rxmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int link_start(struct net_device *dev)
{
	int ret;
	struct port_info *pi = netdev_priv(dev);

	/*
	 * We do not set address filters and promiscuity here, the stack does
	 * that step explicitly. Enable vlan accel.
	 */
	ret = t4vf_set_rxmode(pi->adapter, pi->viid, dev->mtu, -1, -1, -1, 1,
			      true);
	if (ret == 0)
		ret = cxgb4vf_change_mac(pi, pi->viid,
					 &pi->xact_addr_filt,
					 dev->dev_addr, true);

	/*
	 * We don't need to actually "start the link" itself since the
	 * firmware will do that for us when the first Virtual Interface
	 * is enabled on a port.
	 */
	if (ret == 0)
		ret = t4vf_enable_pi(pi->adapter, pi, true, true);

	return ret;
}