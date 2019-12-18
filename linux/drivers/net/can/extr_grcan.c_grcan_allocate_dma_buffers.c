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
struct net_device {int /*<<< orphan*/  dev; } ;
struct grcan_dma_buffer {size_t size; size_t handle; scalar_t__ buf; } ;
struct grcan_dma {size_t base_handle; scalar_t__ base_buf; struct grcan_dma_buffer rx; struct grcan_dma_buffer tx; scalar_t__ base_size; } ;
struct grcan_priv {struct grcan_dma dma; } ;

/* Variables and functions */
 void* ALIGN (size_t,scalar_t__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GRCAN_BUFFER_ALIGNMENT ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,size_t*,int /*<<< orphan*/ ) ; 
 size_t max (size_t,size_t) ; 
 size_t min (size_t,size_t) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int grcan_allocate_dma_buffers(struct net_device *dev,
				      size_t tsize, size_t rsize)
{
	struct grcan_priv *priv = netdev_priv(dev);
	struct grcan_dma *dma = &priv->dma;
	struct grcan_dma_buffer *large = rsize > tsize ? &dma->rx : &dma->tx;
	struct grcan_dma_buffer *small = rsize > tsize ? &dma->tx : &dma->rx;
	size_t shift;

	/* Need a whole number of GRCAN_BUFFER_ALIGNMENT for the large,
	 * i.e. first buffer
	 */
	size_t maxs = max(tsize, rsize);
	size_t lsize = ALIGN(maxs, GRCAN_BUFFER_ALIGNMENT);

	/* Put the small buffer after that */
	size_t ssize = min(tsize, rsize);

	/* Extra GRCAN_BUFFER_ALIGNMENT to allow for alignment */
	dma->base_size = lsize + ssize + GRCAN_BUFFER_ALIGNMENT;
	dma->base_buf = dma_alloc_coherent(&dev->dev,
					   dma->base_size,
					   &dma->base_handle,
					   GFP_KERNEL);

	if (!dma->base_buf)
		return -ENOMEM;

	dma->tx.size = tsize;
	dma->rx.size = rsize;

	large->handle = ALIGN(dma->base_handle, GRCAN_BUFFER_ALIGNMENT);
	small->handle = large->handle + lsize;
	shift = large->handle - dma->base_handle;

	large->buf = dma->base_buf + shift;
	small->buf = large->buf + lsize;

	return 0;
}