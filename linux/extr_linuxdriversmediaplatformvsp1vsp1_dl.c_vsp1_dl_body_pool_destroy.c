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
struct vsp1_dl_body_pool {struct vsp1_dl_body_pool* bodies; int /*<<< orphan*/  dma; scalar_t__ mem; int /*<<< orphan*/  size; TYPE_1__* vsp1; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vsp1_dl_body_pool*) ; 

void vsp1_dl_body_pool_destroy(struct vsp1_dl_body_pool *pool)
{
	if (!pool)
		return;

	if (pool->mem)
		dma_free_wc(pool->vsp1->bus_master, pool->size, pool->mem,
			    pool->dma);

	kfree(pool->bodies);
	kfree(pool);
}