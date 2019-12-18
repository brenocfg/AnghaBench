#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {TYPE_2__* ctrl; } ;
struct nvm_dev {TYPE_1__* q; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *nvme_nvm_create_dma_pool(struct nvm_dev *nvmdev, char *name,
					int size)
{
	struct nvme_ns *ns = nvmdev->q->queuedata;

	return dma_pool_create(name, ns->ctrl->dev, size, PAGE_SIZE, 0);
}