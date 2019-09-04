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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (struct device*) ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int) ; 

__attribute__((used)) static void *xgbe_dma_alloc_node(struct device *dev, size_t size,
				 dma_addr_t *dma, int node)
{
	void *mem;
	int cur_node = dev_to_node(dev);

	set_dev_node(dev, node);
	mem = dma_alloc_coherent(dev, size, dma, GFP_KERNEL);
	set_dev_node(dev, cur_node);

	if (!mem)
		mem = dma_alloc_coherent(dev, size, dma, GFP_KERNEL);

	return mem;
}