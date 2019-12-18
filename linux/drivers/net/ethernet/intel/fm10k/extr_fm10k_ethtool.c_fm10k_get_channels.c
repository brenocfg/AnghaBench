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
struct fm10k_intfc {TYPE_1__* ring_feature; } ;
struct ethtool_channels {int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_other; int /*<<< orphan*/  other_count; int /*<<< orphan*/  max_combined; } ;
struct TYPE_2__ {int /*<<< orphan*/  indices; } ;

/* Variables and functions */
 int /*<<< orphan*/  NON_Q_VECTORS ; 
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  fm10k_max_channels (struct net_device*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_get_channels(struct net_device *dev,
			       struct ethtool_channels *ch)
{
	struct fm10k_intfc *interface = netdev_priv(dev);

	/* report maximum channels */
	ch->max_combined = fm10k_max_channels(dev);

	/* report info for other vector */
	ch->max_other = NON_Q_VECTORS;
	ch->other_count = ch->max_other;

	/* record RSS queues */
	ch->combined_count = interface->ring_feature[RING_F_RSS].indices;
}