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
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
struct ixgbevf_tx_buffer {int dummy; } ;
struct ixgbevf_ring {int count; int size; int /*<<< orphan*/ * tx_buffer_info; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  dev; int /*<<< orphan*/  syncp; int /*<<< orphan*/  netdev; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ixgbevf_adapter* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

int ixgbevf_setup_tx_resources(struct ixgbevf_ring *tx_ring)
{
	struct ixgbevf_adapter *adapter = netdev_priv(tx_ring->netdev);
	int size;

	size = sizeof(struct ixgbevf_tx_buffer) * tx_ring->count;
	tx_ring->tx_buffer_info = vmalloc(size);
	if (!tx_ring->tx_buffer_info)
		goto err;

	u64_stats_init(&tx_ring->syncp);

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * sizeof(union ixgbe_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(tx_ring->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	if (!tx_ring->desc)
		goto err;

	return 0;

err:
	vfree(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = NULL;
	hw_dbg(&adapter->hw, "Unable to allocate memory for the transmit descriptor ring\n");
	return -ENOMEM;
}