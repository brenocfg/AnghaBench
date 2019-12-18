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
struct knav_pool {int num_desc; int /*<<< orphan*/  queue; TYPE_1__* kdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 void* knav_pool_desc_dma_to_virt (struct knav_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_queue_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knav_queue_pop (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void kdesc_empty_pool(struct knav_pool *pool)
{
	dma_addr_t dma;
	unsigned size;
	void *desc;
	int i;

	if (!pool->queue)
		return;

	for (i = 0;; i++) {
		dma = knav_queue_pop(pool->queue, &size);
		if (!dma)
			break;
		desc = knav_pool_desc_dma_to_virt(pool, dma);
		if (!desc) {
			dev_dbg(pool->kdev->dev,
				"couldn't unmap desc, continuing\n");
			continue;
		}
	}
	WARN_ON(i != pool->num_desc);
	knav_queue_close(pool->queue);
}