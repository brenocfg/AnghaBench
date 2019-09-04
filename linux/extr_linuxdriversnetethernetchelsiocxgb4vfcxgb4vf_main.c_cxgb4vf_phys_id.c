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
struct port_info {int /*<<< orphan*/  viid; int /*<<< orphan*/  adapter; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EINVAL ; 
 int ETHTOOL_ID_ACTIVE ; 
 int ETHTOOL_ID_INACTIVE ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4vf_identify_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int cxgb4vf_phys_id(struct net_device *dev,
			   enum ethtool_phys_id_state state)
{
	unsigned int val;
	struct port_info *pi = netdev_priv(dev);

	if (state == ETHTOOL_ID_ACTIVE)
		val = 0xffff;
	else if (state == ETHTOOL_ID_INACTIVE)
		val = 0;
	else
		return -EINVAL;

	return t4vf_identify_port(pi->adapter, pi->viid, val);
}