#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  pf; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
struct TYPE_2__ {int /*<<< orphan*/  viid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETHTOOL_ID_ACTIVE ; 
 int ETHTOOL_ID_INACTIVE ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 TYPE_1__* netdev2pinfo (struct net_device*) ; 
 int t4_identify_port (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int identify_port(struct net_device *dev,
			 enum ethtool_phys_id_state state)
{
	unsigned int val;
	struct adapter *adap = netdev2adap(dev);

	if (state == ETHTOOL_ID_ACTIVE)
		val = 0xffff;
	else if (state == ETHTOOL_ID_INACTIVE)
		val = 0;
	else
		return -EINVAL;

	return t4_identify_port(adap, adap->pf, netdev2pinfo(dev)->viid, val);
}