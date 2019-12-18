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
struct rproc_mem_entry {void* va; int /*<<< orphan*/  len; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {struct device* parent; } ;
struct rproc {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rproc_mem_alloc(struct rproc *rproc,
			      struct rproc_mem_entry *mem)
{
	struct device *dev = rproc->dev.parent;
	void *va;

	va = ioremap_wc(mem->dma, mem->len);
	if (!va) {
		dev_err(dev, "Unable to map memory region: %pa+%zx\n",
			&mem->dma, mem->len);
		return -ENOMEM;
	}

	/* Update memory entry va */
	mem->va = va;

	return 0;
}