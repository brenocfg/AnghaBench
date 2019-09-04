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
struct xilly_mapping {int /*<<< orphan*/  direction; int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void xilly_of_unmap(void *ptr)
{
	struct xilly_mapping *data = ptr;

	dma_unmap_single(data->device, data->dma_addr,
			 data->size, data->direction);

	kfree(ptr);
}