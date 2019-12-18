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
struct nfp_net_tx_ring {int dummy; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_tx_start_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  nfp_net_tx_ring_should_wake (struct nfp_net_tx_ring*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_tx_ring_stop(struct netdev_queue *nd_q,
				 struct nfp_net_tx_ring *tx_ring)
{
	netif_tx_stop_queue(nd_q);

	/* We can race with the TX completion out of NAPI so recheck */
	smp_mb();
	if (unlikely(nfp_net_tx_ring_should_wake(tx_ring)))
		netif_tx_start_queue(nd_q);
}