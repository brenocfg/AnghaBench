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
struct sg_dma_descriptor {int /*<<< orphan*/  next_l; } ;
struct sg_dma_desc_info {struct sg_dma_descriptor* last_desc_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_ENABLE ; 

void descriptor_list_interrupt_disable(struct sg_dma_desc_info *desc)
{
	struct sg_dma_descriptor *d = desc->last_desc_virt;

	d->next_l &= ~INTERRUPT_ENABLE;
}