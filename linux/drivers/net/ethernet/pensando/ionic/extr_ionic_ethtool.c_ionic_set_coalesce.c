#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
struct ionic_qcq {TYPE_4__ intr; } ;
struct ionic_lif {scalar_t__ rx_coalesce_usecs; unsigned int nxqs; TYPE_5__* ionic; TYPE_2__* rxqcqs; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {scalar_t__ intr_coal_div; } ;
struct ionic_identity {TYPE_1__ dev; } ;
struct ethtool_coalesce {scalar_t__ tx_coalesce_usecs; scalar_t__ rx_coalesce_usecs; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ tx_max_coalesced_frames; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames; } ;
struct TYPE_9__ {int /*<<< orphan*/  intr_ctrl; } ;
struct TYPE_11__ {TYPE_3__ idev; struct ionic_identity ident; } ;
struct TYPE_8__ {struct ionic_qcq* qcq; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ERANGE ; 
 scalar_t__ IONIC_INTR_CTRL_COAL_MAX ; 
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 scalar_t__ ionic_coal_hw_to_usec (TYPE_5__*,scalar_t__) ; 
 scalar_t__ ionic_coal_usec_to_hw (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ionic_intr_coal_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ionic_set_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *coalesce)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	struct ionic_identity *ident;
	struct ionic_qcq *qcq;
	unsigned int i;
	u32 usecs;
	u32 coal;

	if (coalesce->rx_max_coalesced_frames ||
	    coalesce->rx_coalesce_usecs_irq ||
	    coalesce->rx_max_coalesced_frames_irq ||
	    coalesce->tx_max_coalesced_frames ||
	    coalesce->tx_coalesce_usecs_irq ||
	    coalesce->tx_max_coalesced_frames_irq ||
	    coalesce->stats_block_coalesce_usecs ||
	    coalesce->use_adaptive_rx_coalesce ||
	    coalesce->use_adaptive_tx_coalesce ||
	    coalesce->pkt_rate_low ||
	    coalesce->rx_coalesce_usecs_low ||
	    coalesce->rx_max_coalesced_frames_low ||
	    coalesce->tx_coalesce_usecs_low ||
	    coalesce->tx_max_coalesced_frames_low ||
	    coalesce->pkt_rate_high ||
	    coalesce->rx_coalesce_usecs_high ||
	    coalesce->rx_max_coalesced_frames_high ||
	    coalesce->tx_coalesce_usecs_high ||
	    coalesce->tx_max_coalesced_frames_high ||
	    coalesce->rate_sample_interval)
		return -EINVAL;

	ident = &lif->ionic->ident;
	if (ident->dev.intr_coal_div == 0) {
		netdev_warn(netdev, "bad HW value in dev.intr_coal_div = %d\n",
			    ident->dev.intr_coal_div);
		return -EIO;
	}

	/* Tx uses Rx interrupt, so only change Rx */
	if (coalesce->tx_coalesce_usecs != lif->rx_coalesce_usecs) {
		netdev_warn(netdev, "only the rx-usecs can be changed\n");
		return -EINVAL;
	}

	coal = ionic_coal_usec_to_hw(lif->ionic, coalesce->rx_coalesce_usecs);

	if (coal > IONIC_INTR_CTRL_COAL_MAX)
		return -ERANGE;

	/* If they asked for non-zero and it resolved to zero, bump it up */
	if (!coal && coalesce->rx_coalesce_usecs)
		coal = 1;

	/* Convert it back to get device resolution */
	usecs = ionic_coal_hw_to_usec(lif->ionic, coal);

	if (usecs != lif->rx_coalesce_usecs) {
		lif->rx_coalesce_usecs = usecs;

		if (test_bit(IONIC_LIF_UP, lif->state)) {
			for (i = 0; i < lif->nxqs; i++) {
				qcq = lif->rxqcqs[i].qcq;
				ionic_intr_coal_init(lif->ionic->idev.intr_ctrl,
						     qcq->intr.index, coal);
			}
		}
	}

	return 0;
}