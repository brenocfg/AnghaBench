#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ring_desc_ex {int /*<<< orphan*/  flaglen; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {struct ring_desc_ex* ex; } ;
struct TYPE_9__ {struct ring_desc_ex* ex; } ;
struct TYPE_8__ {int /*<<< orphan*/  ex; } ;
struct TYPE_7__ {struct ring_desc_ex* ex; } ;
struct fe_priv {int driver_data; int tx_stop; TYPE_4__ get_tx; int /*<<< orphan*/  dev; TYPE_5__* tx_skb; TYPE_5__* get_tx_ctx; int /*<<< orphan*/  last_tx_ctx; TYPE_3__ tx_ring; TYPE_2__ last_tx; scalar_t__ tx_limit; int /*<<< orphan*/  swstats_tx_syncp; TYPE_1__ put_tx; } ;
struct TYPE_12__ {unsigned int len; } ;
struct TYPE_11__ {TYPE_6__* skb; } ;

/* Variables and functions */
 int DEV_HAS_GEAR_MODE ; 
 int NV_TX2_ERROR ; 
 int NV_TX2_LASTPACKET ; 
 int NV_TX2_RETRYCOUNT_MASK ; 
 int NV_TX2_RETRYERROR ; 
 int NV_TX2_VALID ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_6__*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_completed_queue (int /*<<< orphan*/ ,int,unsigned long) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  nv_gear_backoff_reseed (struct net_device*) ; 
 int /*<<< orphan*/  nv_legacybackoff_reseed (struct net_device*) ; 
 int /*<<< orphan*/  nv_tx_flip_ownership (struct net_device*) ; 
 int /*<<< orphan*/  nv_txrx_stats_add (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nv_txrx_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_unmap_txskb (struct fe_priv*,TYPE_5__*) ; 
 int /*<<< orphan*/  stat_tx_bytes ; 
 int /*<<< orphan*/  stat_tx_packets ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nv_tx_done_optimized(struct net_device *dev, int limit)
{
	struct fe_priv *np = netdev_priv(dev);
	u32 flags;
	int tx_work = 0;
	struct ring_desc_ex *orig_get_tx = np->get_tx.ex;
	unsigned long bytes_cleaned = 0;

	while ((np->get_tx.ex != np->put_tx.ex) &&
	       !((flags = le32_to_cpu(np->get_tx.ex->flaglen)) & NV_TX2_VALID) &&
	       (tx_work < limit)) {

		nv_unmap_txskb(np, np->get_tx_ctx);

		if (flags & NV_TX2_LASTPACKET) {
			if (unlikely(flags & NV_TX2_ERROR)) {
				if ((flags & NV_TX2_RETRYERROR)
				    && !(flags & NV_TX2_RETRYCOUNT_MASK)) {
					if (np->driver_data & DEV_HAS_GEAR_MODE)
						nv_gear_backoff_reseed(dev);
					else
						nv_legacybackoff_reseed(dev);
				}
			} else {
				unsigned int len;

				u64_stats_update_begin(&np->swstats_tx_syncp);
				nv_txrx_stats_inc(stat_tx_packets);
				len = np->get_tx_ctx->skb->len;
				nv_txrx_stats_add(stat_tx_bytes, len);
				u64_stats_update_end(&np->swstats_tx_syncp);
			}

			bytes_cleaned += np->get_tx_ctx->skb->len;
			dev_kfree_skb_any(np->get_tx_ctx->skb);
			np->get_tx_ctx->skb = NULL;
			tx_work++;

			if (np->tx_limit)
				nv_tx_flip_ownership(dev);
		}

		if (unlikely(np->get_tx.ex++ == np->last_tx.ex))
			np->get_tx.ex = np->tx_ring.ex;
		if (unlikely(np->get_tx_ctx++ == np->last_tx_ctx))
			np->get_tx_ctx = np->tx_skb;
	}

	netdev_completed_queue(np->dev, tx_work, bytes_cleaned);

	if (unlikely((np->tx_stop == 1) && (np->get_tx.ex != orig_get_tx))) {
		np->tx_stop = 0;
		netif_wake_queue(dev);
	}
	return tx_work;
}