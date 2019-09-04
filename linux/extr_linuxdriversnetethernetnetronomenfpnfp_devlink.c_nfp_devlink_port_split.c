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
struct nfp_pf {int /*<<< orphan*/  lock; } ;
struct nfp_eth_table_port {unsigned int port_lanes; int lanes; int /*<<< orphan*/  index; scalar_t__ is_split; } ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nfp_pf* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfp_devlink_fill_eth_port_from_id (struct nfp_pf*,unsigned int,struct nfp_eth_table_port*) ; 
 int nfp_devlink_set_lanes (struct nfp_pf*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int
nfp_devlink_port_split(struct devlink *devlink, unsigned int port_index,
		       unsigned int count, struct netlink_ext_ack *extack)
{
	struct nfp_pf *pf = devlink_priv(devlink);
	struct nfp_eth_table_port eth_port;
	unsigned int lanes;
	int ret;

	if (count < 2)
		return -EINVAL;

	mutex_lock(&pf->lock);

	rtnl_lock();
	ret = nfp_devlink_fill_eth_port_from_id(pf, port_index, &eth_port);
	rtnl_unlock();
	if (ret)
		goto out;

	if (eth_port.is_split || eth_port.port_lanes % count) {
		ret = -EINVAL;
		goto out;
	}

	/* Special case the 100G CXP -> 2x40G split */
	lanes = eth_port.port_lanes / count;
	if (eth_port.lanes == 10 && count == 2)
		lanes = 8 / count;

	ret = nfp_devlink_set_lanes(pf, eth_port.index, lanes);
out:
	mutex_unlock(&pf->lock);

	return ret;
}