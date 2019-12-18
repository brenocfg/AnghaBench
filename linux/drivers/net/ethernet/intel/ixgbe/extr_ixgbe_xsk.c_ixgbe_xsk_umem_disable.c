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
typedef  int /*<<< orphan*/  u16 ;
struct xdp_umem {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  af_xdp_zc_qps; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_enabled_xdp_adapter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_txrx_ring_disable (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_txrx_ring_enable (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_xsk_umem_dma_unmap (struct ixgbe_adapter*,struct xdp_umem*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 struct xdp_umem* xdp_get_umem_from_qid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_xsk_umem_disable(struct ixgbe_adapter *adapter, u16 qid)
{
	struct xdp_umem *umem;
	bool if_running;

	umem = xdp_get_umem_from_qid(adapter->netdev, qid);
	if (!umem)
		return -EINVAL;

	if_running = netif_running(adapter->netdev) &&
		     ixgbe_enabled_xdp_adapter(adapter);

	if (if_running)
		ixgbe_txrx_ring_disable(adapter, qid);

	clear_bit(qid, adapter->af_xdp_zc_qps);
	ixgbe_xsk_umem_dma_unmap(adapter, umem);

	if (if_running)
		ixgbe_txrx_ring_enable(adapter, qid);

	return 0;
}