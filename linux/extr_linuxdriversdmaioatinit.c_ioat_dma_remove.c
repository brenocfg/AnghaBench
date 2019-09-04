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
struct dma_device {int /*<<< orphan*/  channels; } ;
struct ioatdma_device {int /*<<< orphan*/  completion_pool; struct dma_device dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_disable_interrupts (struct ioatdma_device*) ; 
 int /*<<< orphan*/  ioat_kobject_del (struct ioatdma_device*) ; 

__attribute__((used)) static void ioat_dma_remove(struct ioatdma_device *ioat_dma)
{
	struct dma_device *dma = &ioat_dma->dma_dev;

	ioat_disable_interrupts(ioat_dma);

	ioat_kobject_del(ioat_dma);

	dma_async_device_unregister(dma);

	dma_pool_destroy(ioat_dma->completion_pool);

	INIT_LIST_HEAD(&dma->channels);
}