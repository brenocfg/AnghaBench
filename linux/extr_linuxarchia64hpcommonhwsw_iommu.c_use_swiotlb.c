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
struct device {int /*<<< orphan*/ * dma_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_supported ) (struct device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ sba_dma_ops ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int use_swiotlb(struct device *dev)
{
	return dev && dev->dma_mask &&
		!sba_dma_ops.dma_supported(dev, *dev->dma_mask);
}