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
struct xgbe_ring_desc {int dummy; } ;
struct xgbe_ring_data {int dummy; } ;
struct xgbe_ring {unsigned int rdesc_count; int /*<<< orphan*/  node; int /*<<< orphan*/  rdata; int /*<<< orphan*/  rdesc_dma; int /*<<< orphan*/  rdesc; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_alloc_node (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_dma_alloc_node (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_init_ring(struct xgbe_prv_data *pdata,
			  struct xgbe_ring *ring, unsigned int rdesc_count)
{
	size_t size;

	if (!ring)
		return 0;

	/* Descriptors */
	size = rdesc_count * sizeof(struct xgbe_ring_desc);

	ring->rdesc_count = rdesc_count;
	ring->rdesc = xgbe_dma_alloc_node(pdata->dev, size, &ring->rdesc_dma,
					  ring->node);
	if (!ring->rdesc)
		return -ENOMEM;

	/* Descriptor information */
	size = rdesc_count * sizeof(struct xgbe_ring_data);

	ring->rdata = xgbe_alloc_node(size, ring->node);
	if (!ring->rdata)
		return -ENOMEM;

	netif_dbg(pdata, drv, pdata->netdev,
		  "rdesc=%p, rdesc_dma=%pad, rdata=%p, node=%d\n",
		  ring->rdesc, &ring->rdesc_dma, ring->rdata, ring->node);

	return 0;
}