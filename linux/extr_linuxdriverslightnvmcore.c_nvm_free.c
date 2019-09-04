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
struct nvm_dev {struct nvm_dev* lun_map; scalar_t__ dma_pool; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy_dma_pool ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvm_dev*) ; 
 int /*<<< orphan*/  nvm_unregister_map (struct nvm_dev*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void nvm_free(struct nvm_dev *dev)
{
	if (!dev)
		return;

	if (dev->dma_pool)
		dev->ops->destroy_dma_pool(dev->dma_pool);

	nvm_unregister_map(dev);
	kfree(dev->lun_map);
	kfree(dev);
}