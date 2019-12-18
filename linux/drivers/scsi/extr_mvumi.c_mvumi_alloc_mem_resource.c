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
struct mvumi_res {int type; unsigned int size; int /*<<< orphan*/  entry; void* virt_addr; int /*<<< orphan*/  bus_addr; } ;
struct mvumi_hba {int /*<<< orphan*/  res_list; TYPE_1__* pdev; } ;
typedef  enum resource_type { ____Placeholder_resource_type } resource_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  RESOURCE_CACHED_MEMORY 129 
#define  RESOURCE_UNCACHED_MEMORY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mvumi_res*) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int round_up (unsigned int,int) ; 

__attribute__((used)) static struct mvumi_res *mvumi_alloc_mem_resource(struct mvumi_hba *mhba,
				enum resource_type type, unsigned int size)
{
	struct mvumi_res *res = kzalloc(sizeof(*res), GFP_ATOMIC);

	if (!res) {
		dev_err(&mhba->pdev->dev,
			"Failed to allocate memory for resource manager.\n");
		return NULL;
	}

	switch (type) {
	case RESOURCE_CACHED_MEMORY:
		res->virt_addr = kzalloc(size, GFP_ATOMIC);
		if (!res->virt_addr) {
			dev_err(&mhba->pdev->dev,
				"unable to allocate memory,size = %d.\n", size);
			kfree(res);
			return NULL;
		}
		break;

	case RESOURCE_UNCACHED_MEMORY:
		size = round_up(size, 8);
		res->virt_addr = dma_alloc_coherent(&mhba->pdev->dev, size,
						    &res->bus_addr,
						    GFP_KERNEL);
		if (!res->virt_addr) {
			dev_err(&mhba->pdev->dev,
					"unable to allocate consistent mem,"
							"size = %d.\n", size);
			kfree(res);
			return NULL;
		}
		break;

	default:
		dev_err(&mhba->pdev->dev, "unknown resource type %d.\n", type);
		kfree(res);
		return NULL;
	}

	res->type = type;
	res->size = size;
	INIT_LIST_HEAD(&res->entry);
	list_add_tail(&res->entry, &mhba->res_list);

	return res;
}