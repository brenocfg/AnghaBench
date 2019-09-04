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
struct netdev_queue {int dummy; } ;
struct fm10k_ring {size_t queue_index; TYPE_1__* netdev; } ;
struct TYPE_2__ {struct netdev_queue* _tx; } ;

/* Variables and functions */

__attribute__((used)) static inline struct netdev_queue *txring_txq(const struct fm10k_ring *ring)
{
	return &ring->netdev->_tx[ring->queue_index];
}