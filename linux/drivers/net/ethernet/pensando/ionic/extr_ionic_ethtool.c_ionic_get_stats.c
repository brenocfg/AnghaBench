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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {int dummy; } ;
struct ethtool_stats {int n_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_values ) (struct ionic_lif*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 size_t ionic_num_stats_grps ; 
 TYPE_1__* ionic_stats_groups ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ionic_lif*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void ionic_get_stats(struct net_device *netdev,
			    struct ethtool_stats *stats, u64 *buf)
{
	struct ionic_lif *lif;
	u32 i;

	lif = netdev_priv(netdev);

	memset(buf, 0, stats->n_stats * sizeof(*buf));
	for (i = 0; i < ionic_num_stats_grps; i++)
		ionic_stats_groups[i].get_values(lif, &buf);
}