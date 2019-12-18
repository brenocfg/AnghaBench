#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct veth_rq_stats {int /*<<< orphan*/  syncp; } ;
struct veth_priv {TYPE_1__* rq; int /*<<< orphan*/  peer; } ;
struct net_device {int real_num_rx_queues; int /*<<< orphan*/  ifindex; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {size_t offset; } ;
struct TYPE_3__ {struct veth_rq_stats stats; } ;

/* Variables and functions */
 int VETH_RQ_STATS_LEN ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_2__* veth_rq_stats_desc ; 

__attribute__((used)) static void veth_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct veth_priv *priv = netdev_priv(dev);
	struct net_device *peer = rtnl_dereference(priv->peer);
	int i, j, idx;

	data[0] = peer ? peer->ifindex : 0;
	idx = 1;
	for (i = 0; i < dev->real_num_rx_queues; i++) {
		const struct veth_rq_stats *rq_stats = &priv->rq[i].stats;
		const void *stats_base = (void *)rq_stats;
		unsigned int start;
		size_t offset;

		do {
			start = u64_stats_fetch_begin_irq(&rq_stats->syncp);
			for (j = 0; j < VETH_RQ_STATS_LEN; j++) {
				offset = veth_rq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			}
		} while (u64_stats_fetch_retry_irq(&rq_stats->syncp, start));
		idx += VETH_RQ_STATS_LEN;
	}
}