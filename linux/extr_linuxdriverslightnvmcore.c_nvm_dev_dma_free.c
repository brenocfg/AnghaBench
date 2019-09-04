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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* dev_dma_free ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void nvm_dev_dma_free(struct nvm_dev *dev, void *addr, dma_addr_t dma_handler)
{
	dev->ops->dev_dma_free(dev->dma_pool, addr, dma_handler);
}