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
struct rproc_mem_entry {int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  len; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct rproc {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rproc_release_carveout(struct rproc *rproc,
				  struct rproc_mem_entry *mem)
{
	struct device *dev = &rproc->dev;

	/* clean up carveout allocations */
	dma_free_coherent(dev->parent, mem->len, mem->va, mem->dma);
	return 0;
}