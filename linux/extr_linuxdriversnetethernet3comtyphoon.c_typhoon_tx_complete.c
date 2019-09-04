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
typedef  int /*<<< orphan*/  u32 ;
struct typhoon {int /*<<< orphan*/  dev; } ;
struct transmit_ring {int /*<<< orphan*/  lastRead; int /*<<< orphan*/  lastWrite; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  TXLO_ENTRIES ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  typhoon_clean_tx (struct typhoon*,struct transmit_ring*,int /*<<< orphan*/  volatile*) ; 
 int typhoon_num_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
typhoon_tx_complete(struct typhoon *tp, struct transmit_ring *txRing,
			volatile __le32 * index)
{
	u32 lastRead;
	int numDesc = MAX_SKB_FRAGS + 1;

	/* This will need changing if we start to use the Hi Tx ring. */
	lastRead = typhoon_clean_tx(tp, txRing, index);
	if(netif_queue_stopped(tp->dev) && typhoon_num_free(txRing->lastWrite,
				lastRead, TXLO_ENTRIES) > (numDesc + 2))
		netif_wake_queue(tp->dev);

	txRing->lastRead = lastRead;
	smp_wmb();
}