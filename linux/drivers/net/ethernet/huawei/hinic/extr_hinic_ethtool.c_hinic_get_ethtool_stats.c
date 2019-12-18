#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct hinic_vport_stats {int /*<<< orphan*/  member_0; } ;
struct hinic_phy_port_stats {int dummy; } ;
struct hinic_dev {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {int offset; int size; } ;

/* Variables and functions */
 size_t ARRAY_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  get_drv_queue_stats (struct hinic_dev*,int /*<<< orphan*/ *) ; 
 TYPE_1__* hinic_function_stats ; 
 int hinic_get_phy_port_stats (struct hinic_dev*,struct hinic_phy_port_stats*) ; 
 int hinic_get_vport_stats (struct hinic_dev*,struct hinic_vport_stats*) ; 
 TYPE_1__* hinic_port_stats ; 
 int /*<<< orphan*/  kfree (struct hinic_phy_port_stats*) ; 
 struct hinic_phy_port_stats* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static void hinic_get_ethtool_stats(struct net_device *netdev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	struct hinic_vport_stats vport_stats = {0};
	struct hinic_phy_port_stats *port_stats;
	u16 i = 0, j = 0;
	char *p;
	int err;

	err = hinic_get_vport_stats(nic_dev, &vport_stats);
	if (err)
		netif_err(nic_dev, drv, netdev,
			  "Failed to get vport stats from firmware\n");

	for (j = 0; j < ARRAY_LEN(hinic_function_stats); j++, i++) {
		p = (char *)&vport_stats + hinic_function_stats[j].offset;
		data[i] = (hinic_function_stats[j].size ==
				sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}

	port_stats = kzalloc(sizeof(*port_stats), GFP_KERNEL);
	if (!port_stats) {
		memset(&data[i], 0,
		       ARRAY_LEN(hinic_port_stats) * sizeof(*data));
		i += ARRAY_LEN(hinic_port_stats);
		goto get_drv_stats;
	}

	err = hinic_get_phy_port_stats(nic_dev, port_stats);
	if (err)
		netif_err(nic_dev, drv, netdev,
			  "Failed to get port stats from firmware\n");

	for (j = 0; j < ARRAY_LEN(hinic_port_stats); j++, i++) {
		p = (char *)port_stats + hinic_port_stats[j].offset;
		data[i] = (hinic_port_stats[j].size ==
				sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}

	kfree(port_stats);

get_drv_stats:
	get_drv_queue_stats(nic_dev, data + i);
}