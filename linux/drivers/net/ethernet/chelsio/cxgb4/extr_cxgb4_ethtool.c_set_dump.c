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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_dump {int /*<<< orphan*/  flag; } ;
struct cudbg_hdr {int dummy; } ;
struct cudbg_entity_hdr {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  flag; } ;
struct adapter {TYPE_1__ eth_dump; } ;

/* Variables and functions */
 int CUDBG_MAX_ENTITY ; 
 scalar_t__ cxgb4_get_dump_length (struct adapter*,int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device*) ; 

__attribute__((used)) static int set_dump(struct net_device *dev, struct ethtool_dump *eth_dump)
{
	struct adapter *adapter = netdev2adap(dev);
	u32 len = 0;

	len = sizeof(struct cudbg_hdr) +
	      sizeof(struct cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += cxgb4_get_dump_length(adapter, eth_dump->flag);

	adapter->eth_dump.flag = eth_dump->flag;
	adapter->eth_dump.len = len;
	return 0;
}