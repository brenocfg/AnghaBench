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
struct mtk_tx_ring {scalar_t__ thresh; int /*<<< orphan*/  free_count; } ;
struct mtk_eth {int /*<<< orphan*/ * netdev; TYPE_1__* soc; struct mtk_tx_ring tx_ring; } ;
typedef  int /*<<< orphan*/  done ;
typedef  int /*<<< orphan*/  bytes ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MTK_MAC_COUNT ; 
 int MTK_MAX_DEVS ; 
 int /*<<< orphan*/  MTK_QDMA ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int mtk_poll_tx_pdma (struct mtk_eth*,int,unsigned int*,unsigned int*) ; 
 int mtk_poll_tx_qdma (struct mtk_eth*,int,unsigned int*,unsigned int*) ; 
 scalar_t__ mtk_queue_stopped (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_wake_queue (struct mtk_eth*) ; 
 int /*<<< orphan*/  netdev_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int mtk_poll_tx(struct mtk_eth *eth, int budget)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	unsigned int done[MTK_MAX_DEVS];
	unsigned int bytes[MTK_MAX_DEVS];
	int total = 0, i;

	memset(done, 0, sizeof(done));
	memset(bytes, 0, sizeof(bytes));

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		budget = mtk_poll_tx_qdma(eth, budget, done, bytes);
	else
		budget = mtk_poll_tx_pdma(eth, budget, done, bytes);

	for (i = 0; i < MTK_MAC_COUNT; i++) {
		if (!eth->netdev[i] || !done[i])
			continue;
		netdev_completed_queue(eth->netdev[i], done[i], bytes[i]);
		total += done[i];
	}

	if (mtk_queue_stopped(eth) &&
	    (atomic_read(&ring->free_count) > ring->thresh))
		mtk_wake_queue(eth);

	return total;
}