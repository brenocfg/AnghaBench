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
typedef  int /*<<< orphan*/  u64 ;
struct t4vf_port_stats {int dummy; } ;
struct queue_port_stats {int dummy; } ;
struct port_info {int /*<<< orphan*/  pidx; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_sge_port_stats (struct adapter*,struct port_info*,struct queue_port_stats*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int t4vf_get_port_stats (struct adapter*,int /*<<< orphan*/ ,struct t4vf_port_stats*) ; 

__attribute__((used)) static void cxgb4vf_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats,
				      u64 *data)
{
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adapter = pi->adapter;
	int err = t4vf_get_port_stats(adapter, pi->pidx,
				      (struct t4vf_port_stats *)data);
	if (err)
		memset(data, 0, sizeof(struct t4vf_port_stats));

	data += sizeof(struct t4vf_port_stats) / sizeof(u64);
	collect_sge_port_stats(adapter, pi, (struct queue_port_stats *)data);
}