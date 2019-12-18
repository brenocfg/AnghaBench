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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ixgbe_ring {TYPE_1__* q_vector; int /*<<< orphan*/  xsk_umem; } ;
struct ixgbe_adapter {size_t num_xdp_queues; struct ixgbe_ring** xdp_ring; int /*<<< orphan*/  xdp_prog; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_idx; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int ENETDOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  ixgbe_irq_rearm_queues (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_if_scheduled_mark_missed (int /*<<< orphan*/ *) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbe_xsk_wakeup(struct net_device *dev, u32 qid, u32 flags)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ixgbe_ring *ring;

	if (test_bit(__IXGBE_DOWN, &adapter->state))
		return -ENETDOWN;

	if (!READ_ONCE(adapter->xdp_prog))
		return -ENXIO;

	if (qid >= adapter->num_xdp_queues)
		return -ENXIO;

	if (!adapter->xdp_ring[qid]->xsk_umem)
		return -ENXIO;

	ring = adapter->xdp_ring[qid];
	if (!napi_if_scheduled_mark_missed(&ring->q_vector->napi)) {
		u64 eics = BIT_ULL(ring->q_vector->v_idx);

		ixgbe_irq_rearm_queues(adapter, eics);
	}

	return 0;
}