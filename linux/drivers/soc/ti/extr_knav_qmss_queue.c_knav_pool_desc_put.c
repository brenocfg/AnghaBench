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
struct knav_pool {TYPE_1__* region; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  desc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  knav_pool_desc_virt_to_dma (struct knav_pool*,void*) ; 
 int /*<<< orphan*/  knav_queue_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void knav_pool_desc_put(void *ph, void *desc)
{
	struct knav_pool *pool = ph;
	dma_addr_t dma;
	dma = knav_pool_desc_virt_to_dma(pool, desc);
	knav_queue_push(pool->queue, dma, pool->region->desc_size, 0);
}