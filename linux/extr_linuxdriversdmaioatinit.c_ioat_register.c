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
struct ioatdma_device {int /*<<< orphan*/  completion_pool; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int dma_async_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_disable_interrupts (struct ioatdma_device*) ; 

__attribute__((used)) static int ioat_register(struct ioatdma_device *ioat_dma)
{
	int err = dma_async_device_register(&ioat_dma->dma_dev);

	if (err) {
		ioat_disable_interrupts(ioat_dma);
		dma_pool_destroy(ioat_dma->completion_pool);
	}

	return err;
}