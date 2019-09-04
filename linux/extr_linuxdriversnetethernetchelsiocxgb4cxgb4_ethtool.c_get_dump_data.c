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
struct ethtool_dump {int len; scalar_t__ flag; int /*<<< orphan*/  version; } ;
struct cudbg_hdr {int dummy; } ;
struct cudbg_entity_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ flag; int /*<<< orphan*/  version; } ;
struct adapter {TYPE_1__ eth_dump; } ;

/* Variables and functions */
 int CUDBG_MAX_ENTITY ; 
 scalar_t__ CXGB4_ETH_DUMP_NONE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int cxgb4_cudbg_collect (struct adapter*,void*,int*,scalar_t__) ; 
 scalar_t__ cxgb4_get_dump_length (struct adapter*,scalar_t__) ; 
 struct adapter* netdev2adap (struct net_device*) ; 

__attribute__((used)) static int get_dump_data(struct net_device *dev, struct ethtool_dump *eth_dump,
			 void *buf)
{
	struct adapter *adapter = netdev2adap(dev);
	u32 len = 0;
	int ret = 0;

	if (adapter->eth_dump.flag == CXGB4_ETH_DUMP_NONE)
		return -ENOENT;

	len = sizeof(struct cudbg_hdr) +
	      sizeof(struct cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += cxgb4_get_dump_length(adapter, adapter->eth_dump.flag);
	if (eth_dump->len < len)
		return -ENOMEM;

	ret = cxgb4_cudbg_collect(adapter, buf, &len, adapter->eth_dump.flag);
	if (ret)
		return ret;

	eth_dump->flag = adapter->eth_dump.flag;
	eth_dump->len = len;
	eth_dump->version = adapter->eth_dump.version;
	return 0;
}