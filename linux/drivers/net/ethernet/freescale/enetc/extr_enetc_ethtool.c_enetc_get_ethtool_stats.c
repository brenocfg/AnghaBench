#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct enetc_ndev_priv {int num_tx_rings; int num_rx_rings; TYPE_5__* si; TYPE_4__** rx_ring; TYPE_2__** tx_ring; } ;
struct enetc_hw {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  reg; } ;
struct TYPE_13__ {struct enetc_hw hw; } ;
struct TYPE_11__ {int /*<<< orphan*/  rx_alloc_errs; int /*<<< orphan*/  packets; } ;
struct TYPE_12__ {TYPE_3__ stats; } ;
struct TYPE_9__ {int /*<<< orphan*/  packets; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 TYPE_6__* enetc_port_counters ; 
 int /*<<< orphan*/  enetc_port_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_rd64 (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 TYPE_6__* enetc_si_counters ; 
 int /*<<< orphan*/  enetc_si_is_pf (TYPE_5__*) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enetc_get_ethtool_stats(struct net_device *ndev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_hw *hw = &priv->si->hw;
	int i, o = 0;

	for (i = 0; i < ARRAY_SIZE(enetc_si_counters); i++)
		data[o++] = enetc_rd64(hw, enetc_si_counters[i].reg);

	for (i = 0; i < priv->num_tx_rings; i++)
		data[o++] = priv->tx_ring[i]->stats.packets;

	for (i = 0; i < priv->num_rx_rings; i++) {
		data[o++] = priv->rx_ring[i]->stats.packets;
		data[o++] = priv->rx_ring[i]->stats.rx_alloc_errs;
	}

	if (!enetc_si_is_pf(priv->si))
		return;

	for (i = 0; i < ARRAY_SIZE(enetc_port_counters); i++)
		data[o++] = enetc_port_rd(hw, enetc_port_counters[i].reg);
}