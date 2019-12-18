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
typedef  size_t u64 ;
struct TYPE_2__ {scalar_t__ phys_base; int /*<<< orphan*/ * virt_base; scalar_t__ length_bytes; } ;
struct gasket_dev {TYPE_1__ coherent_buffer; int /*<<< orphan*/ * page_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gasket_get_device (struct gasket_dev*) ; 

void gasket_free_coherent_memory_all(struct gasket_dev *gasket_dev, u64 index)
{
	if (!gasket_dev->page_table[index])
		return;

	if (gasket_dev->coherent_buffer.length_bytes) {
		dma_free_coherent(gasket_get_device(gasket_dev),
				  gasket_dev->coherent_buffer.length_bytes,
				  gasket_dev->coherent_buffer.virt_base,
				  gasket_dev->coherent_buffer.phys_base);
		gasket_dev->coherent_buffer.length_bytes = 0;
		gasket_dev->coherent_buffer.virt_base = NULL;
		gasket_dev->coherent_buffer.phys_base = 0;
	}
}