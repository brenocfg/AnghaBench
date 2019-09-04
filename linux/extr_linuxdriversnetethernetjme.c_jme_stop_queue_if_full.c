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
struct jme_ring {int /*<<< orphan*/  nr_free; int /*<<< orphan*/  next_to_clean; struct jme_buffer_info* bufinf; } ;
struct jme_buffer_info {scalar_t__ start_xmit; scalar_t__ skb; } ;
struct jme_adapter {int tx_wake_threshold; int /*<<< orphan*/  dev; struct jme_ring* txring; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 scalar_t__ TX_TIMEOUT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netif_info (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  tx_queued ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
jme_stop_queue_if_full(struct jme_adapter *jme)
{
	struct jme_ring *txring = &(jme->txring[0]);
	struct jme_buffer_info *txbi = txring->bufinf;
	int idx = atomic_read(&txring->next_to_clean);

	txbi += idx;

	smp_wmb();
	if (unlikely(atomic_read(&txring->nr_free) < (MAX_SKB_FRAGS+2))) {
		netif_stop_queue(jme->dev);
		netif_info(jme, tx_queued, jme->dev, "TX Queue Paused\n");
		smp_wmb();
		if (atomic_read(&txring->nr_free)
			>= (jme->tx_wake_threshold)) {
			netif_wake_queue(jme->dev);
			netif_info(jme, tx_queued, jme->dev, "TX Queue Fast Waked\n");
		}
	}

	if (unlikely(txbi->start_xmit &&
			(jiffies - txbi->start_xmit) >= TX_TIMEOUT &&
			txbi->skb)) {
		netif_stop_queue(jme->dev);
		netif_info(jme, tx_queued, jme->dev,
			   "TX Queue Stopped %d@%lu\n", idx, jiffies);
	}
}