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
struct knav_pool {TYPE_1__* region; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int dma_start; void* virt_start; } ;

/* Variables and functions */

dma_addr_t knav_pool_desc_virt_to_dma(void *ph, void *virt)
{
	struct knav_pool *pool = ph;
	return pool->region->dma_start + (virt - pool->region->virt_start);
}