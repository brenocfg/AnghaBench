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
struct nvm_dev {int /*<<< orphan*/  dma_pool; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {void* (* dev_dma_alloc ) (struct nvm_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void* stub1 (struct nvm_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *nvm_dev_dma_alloc(struct nvm_dev *dev, gfp_t mem_flags,
							dma_addr_t *dma_handler)
{
	return dev->ops->dev_dma_alloc(dev, dev->dma_pool, mem_flags,
								dma_handler);
}