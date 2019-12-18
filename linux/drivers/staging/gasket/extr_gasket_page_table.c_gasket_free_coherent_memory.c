#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct TYPE_4__ {scalar_t__ base; } ;
struct gasket_driver_desc {TYPE_1__ coherent_buffer_description; } ;
struct TYPE_5__ {scalar_t__ phys_base; int /*<<< orphan*/ * virt_base; scalar_t__ length_bytes; } ;
struct gasket_dev {TYPE_3__** page_table; TYPE_2__ coherent_buffer; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {scalar_t__ num_coherent_pages; int /*<<< orphan*/ * coherent_pages; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EFAULT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gasket_get_device (struct gasket_dev*) ; 
 struct gasket_driver_desc* gasket_get_driver_desc (struct gasket_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int gasket_free_coherent_memory(struct gasket_dev *gasket_dev, u64 size,
				dma_addr_t dma_address, u64 index)
{
	const struct gasket_driver_desc *driver_desc;

	if (!gasket_dev->page_table[index])
		return -EFAULT;

	driver_desc = gasket_get_driver_desc(gasket_dev);

	if (driver_desc->coherent_buffer_description.base != dma_address)
		return -EADDRNOTAVAIL;

	if (gasket_dev->coherent_buffer.length_bytes) {
		dma_free_coherent(gasket_get_device(gasket_dev),
				  gasket_dev->coherent_buffer.length_bytes,
				  gasket_dev->coherent_buffer.virt_base,
				  gasket_dev->coherent_buffer.phys_base);
		gasket_dev->coherent_buffer.length_bytes = 0;
		gasket_dev->coherent_buffer.virt_base = NULL;
		gasket_dev->coherent_buffer.phys_base = 0;
	}

	kfree(gasket_dev->page_table[index]->coherent_pages);
	gasket_dev->page_table[index]->coherent_pages = NULL;
	gasket_dev->page_table[index]->num_coherent_pages = 0;

	return 0;
}