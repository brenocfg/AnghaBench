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
struct dpaa2_io_store {int max; struct dpaa2_io_store* alloced_addr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  dev; } ;
struct dpaa2_dq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dpaa2_io_store*) ; 

void dpaa2_io_store_destroy(struct dpaa2_io_store *s)
{
	dma_unmap_single(s->dev, s->paddr, sizeof(struct dpaa2_dq) * s->max,
			 DMA_FROM_DEVICE);
	kfree(s->alloced_addr);
	kfree(s);
}