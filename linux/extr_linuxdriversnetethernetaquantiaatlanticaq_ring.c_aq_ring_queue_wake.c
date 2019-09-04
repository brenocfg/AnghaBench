#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_restarts; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct aq_ring_s {TYPE_2__ stats; int /*<<< orphan*/  idx; int /*<<< orphan*/  aq_nic; } ;

/* Variables and functions */
 scalar_t__ __netif_subqueue_stopped (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* aq_nic_get_ndev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (struct net_device*,int /*<<< orphan*/ ) ; 

void aq_ring_queue_wake(struct aq_ring_s *ring)
{
	struct net_device *ndev = aq_nic_get_ndev(ring->aq_nic);

	if (__netif_subqueue_stopped(ndev, ring->idx)) {
		netif_wake_subqueue(ndev, ring->idx);
		ring->stats.tx.queue_restarts++;
	}
}