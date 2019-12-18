#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int tx_bytes; int tx_packets; } ;
struct net_device {TYPE_4__ stats; } ;
struct ag71xx_ring {int dirty; int curr; TYPE_3__* buf; int /*<<< orphan*/  order; } ;
struct ag71xx_desc {int /*<<< orphan*/  ctrl; } ;
struct ag71xx {int /*<<< orphan*/  restart_work; struct net_device* ndev; TYPE_1__* dcfg; struct ag71xx_ring tx_ring; } ;
struct TYPE_6__ {scalar_t__ len; struct sk_buff* skb; } ;
struct TYPE_7__ {TYPE_2__ tx; } ;
struct TYPE_5__ {scalar_t__ tx_hang_workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_TX_STATUS ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 int HZ ; 
 int /*<<< orphan*/  TX_STATUS_PS ; 
 scalar_t__ ag71xx_check_dma_stuck (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_desc_empty (struct ag71xx_desc*) ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,unsigned int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,int,int) ; 
 int /*<<< orphan*/  netif_dbg (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  tx_queued ; 

__attribute__((used)) static int ag71xx_tx_packets(struct ag71xx *ag, bool flush)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	int sent = 0, bytes_compl = 0, n = 0;
	struct net_device *ndev = ag->ndev;
	int ring_mask, ring_size;
	bool dma_stuck = false;

	ring_mask = BIT(ring->order) - 1;
	ring_size = BIT(ring->order);

	netif_dbg(ag, tx_queued, ndev, "processing TX ring\n");

	while (ring->dirty + n != ring->curr) {
		struct ag71xx_desc *desc;
		struct sk_buff *skb;
		unsigned int i;

		i = (ring->dirty + n) & ring_mask;
		desc = ag71xx_ring_desc(ring, i);
		skb = ring->buf[i].tx.skb;

		if (!flush && !ag71xx_desc_empty(desc)) {
			if (ag->dcfg->tx_hang_workaround &&
			    ag71xx_check_dma_stuck(ag)) {
				schedule_delayed_work(&ag->restart_work,
						      HZ / 2);
				dma_stuck = true;
			}
			break;
		}

		if (flush)
			desc->ctrl |= DESC_EMPTY;

		n++;
		if (!skb)
			continue;

		dev_kfree_skb_any(skb);
		ring->buf[i].tx.skb = NULL;

		bytes_compl += ring->buf[i].tx.len;

		sent++;
		ring->dirty += n;

		while (n > 0) {
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
			n--;
		}
	}

	netif_dbg(ag, tx_done, ndev, "%d packets sent out\n", sent);

	if (!sent)
		return 0;

	ag->ndev->stats.tx_bytes += bytes_compl;
	ag->ndev->stats.tx_packets += sent;

	netdev_completed_queue(ag->ndev, sent, bytes_compl);
	if ((ring->curr - ring->dirty) < (ring_size * 3) / 4)
		netif_wake_queue(ag->ndev);

	if (!dma_stuck)
		cancel_delayed_work(&ag->restart_work);

	return sent;
}