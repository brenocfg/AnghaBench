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
struct ethtool_dump {int /*<<< orphan*/  version; int /*<<< orphan*/  len; int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  len; int /*<<< orphan*/  flag; } ;
struct adapter {TYPE_1__ eth_dump; } ;

/* Variables and functions */
 struct adapter* netdev2adap (struct net_device*) ; 

__attribute__((used)) static int get_dump_flag(struct net_device *dev, struct ethtool_dump *eth_dump)
{
	struct adapter *adapter = netdev2adap(dev);

	eth_dump->flag = adapter->eth_dump.flag;
	eth_dump->len = adapter->eth_dump.len;
	eth_dump->version = adapter->eth_dump.version;
	return 0;
}