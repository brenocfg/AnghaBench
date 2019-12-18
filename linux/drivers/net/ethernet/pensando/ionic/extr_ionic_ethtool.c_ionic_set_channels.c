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
struct net_device {int dummy; } ;
struct ionic_lif {scalar_t__ nxqs; int /*<<< orphan*/  state; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ tx_count; scalar_t__ rx_count; scalar_t__ other_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IONIC_LIF_QUEUE_RESET ; 
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_open (struct net_device*) ; 
 int /*<<< orphan*/  ionic_stop (struct net_device*) ; 
 int /*<<< orphan*/  ionic_wait_for_bit (struct ionic_lif*,int /*<<< orphan*/ ) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ionic_set_channels(struct net_device *netdev,
			      struct ethtool_channels *ch)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	bool running;

	if (!ch->combined_count || ch->other_count ||
	    ch->rx_count || ch->tx_count)
		return -EINVAL;

	if (ch->combined_count == lif->nxqs)
		return 0;

	if (!ionic_wait_for_bit(lif, IONIC_LIF_QUEUE_RESET))
		return -EBUSY;

	running = test_bit(IONIC_LIF_UP, lif->state);
	if (running)
		ionic_stop(netdev);

	lif->nxqs = ch->combined_count;

	if (running)
		ionic_open(netdev);
	clear_bit(IONIC_LIF_QUEUE_RESET, lif->state);

	return 0;
}