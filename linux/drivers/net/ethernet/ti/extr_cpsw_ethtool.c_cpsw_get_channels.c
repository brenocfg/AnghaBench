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
struct ethtool_channels {int max_rx; int max_tx; scalar_t__ combined_count; int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; scalar_t__ other_count; scalar_t__ max_other; scalar_t__ max_combined; } ;
struct cpsw_common {int /*<<< orphan*/  tx_ch_num; int /*<<< orphan*/  rx_ch_num; scalar_t__ quirk_irq; } ;

/* Variables and functions */
 int CPSW_MAX_QUEUES ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

void cpsw_get_channels(struct net_device *ndev, struct ethtool_channels *ch)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	ch->max_rx = cpsw->quirk_irq ? 1 : CPSW_MAX_QUEUES;
	ch->max_tx = cpsw->quirk_irq ? 1 : CPSW_MAX_QUEUES;
	ch->max_combined = 0;
	ch->max_other = 0;
	ch->other_count = 0;
	ch->rx_count = cpsw->rx_ch_num;
	ch->tx_count = cpsw->tx_ch_num;
	ch->combined_count = 0;
}