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
typedef  union i40e_32byte_rx_desc {int dummy; } i40e_32byte_rx_desc ;
struct i40e_rx_buffer {int dummy; } ;
struct i40e_ring {int count; int size; int /*<<< orphan*/ * rx_bi; TYPE_1__* vsi; int /*<<< orphan*/  xdp_prog; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; int /*<<< orphan*/  xdp_rxq; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ next_to_alloc; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  syncp; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int xdp_rxq_info_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i40e_setup_rx_descriptors(struct i40e_ring *rx_ring)
{
	struct device *dev = rx_ring->dev;
	int err = -ENOMEM;
	int bi_size;

	/* warn if we are about to overwrite the pointer */
	WARN_ON(rx_ring->rx_bi);
	bi_size = sizeof(struct i40e_rx_buffer) * rx_ring->count;
	rx_ring->rx_bi = kzalloc(bi_size, GFP_KERNEL);
	if (!rx_ring->rx_bi)
		goto err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * sizeof(union i40e_32byte_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);
	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	if (!rx_ring->desc) {
		dev_info(dev, "Unable to allocate memory for the Rx descriptor ring, size=%d\n",
			 rx_ring->size);
		goto err;
	}

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	/* XDP RX-queue info only needed for RX rings exposed to XDP */
	if (rx_ring->vsi->type == I40E_VSI_MAIN) {
		err = xdp_rxq_info_reg(&rx_ring->xdp_rxq, rx_ring->netdev,
				       rx_ring->queue_index);
		if (err < 0)
			goto err;
	}

	rx_ring->xdp_prog = rx_ring->vsi->xdp_prog;

	return 0;
err:
	kfree(rx_ring->rx_bi);
	rx_ring->rx_bi = NULL;
	return err;
}