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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb_alloc_fail; } ;
struct ena_ring {int /*<<< orphan*/  netdev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  syncp; TYPE_1__ rx_stats; int /*<<< orphan*/  rx_copybreak; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ena_alloc_skb(struct ena_ring *rx_ring, bool frags)
{
	struct sk_buff *skb;

	if (frags)
		skb = napi_get_frags(rx_ring->napi);
	else
		skb = netdev_alloc_skb_ip_align(rx_ring->netdev,
						rx_ring->rx_copybreak);

	if (unlikely(!skb)) {
		u64_stats_update_begin(&rx_ring->syncp);
		rx_ring->rx_stats.skb_alloc_fail++;
		u64_stats_update_end(&rx_ring->syncp);
		netif_dbg(rx_ring->adapter, rx_err, rx_ring->netdev,
			  "Failed to allocate skb. frags: %d\n", frags);
		return NULL;
	}

	return skb;
}