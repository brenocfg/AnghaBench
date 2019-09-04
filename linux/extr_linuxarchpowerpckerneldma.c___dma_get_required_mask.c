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
typedef  int /*<<< orphan*/  u64 ;
struct dma_map_ops {int /*<<< orphan*/  (* get_required_mask ) (struct device*) ;} ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

u64 __dma_get_required_mask(struct device *dev)
{
	const struct dma_map_ops *dma_ops = get_dma_ops(dev);

	if (unlikely(dma_ops == NULL))
		return 0;

	if (dma_ops->get_required_mask)
		return dma_ops->get_required_mask(dev);

	return DMA_BIT_MASK(8 * sizeof(dma_addr_t));
}