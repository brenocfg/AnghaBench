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
struct ionic_lif {int /*<<< orphan*/  nxqs; TYPE_1__* ionic; } ;
struct ethtool_channels {int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_combined; } ;
struct TYPE_2__ {int /*<<< orphan*/  ntxqs_per_lif; } ;

/* Variables and functions */
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ionic_get_channels(struct net_device *netdev,
			       struct ethtool_channels *ch)
{
	struct ionic_lif *lif = netdev_priv(netdev);

	/* report maximum channels */
	ch->max_combined = lif->ionic->ntxqs_per_lif;

	/* report current channels */
	ch->combined_count = lif->nxqs;
}