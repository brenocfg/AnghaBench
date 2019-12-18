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
struct sg_dma_desc_info {size_t size; void* virt; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *descriptor_list_allocate(struct sg_dma_desc_info *desc, size_t bytes)
{
	desc->size = bytes;
	desc->virt = dma_alloc_coherent(desc->dev, bytes,
					&desc->bus, GFP_KERNEL);
	return desc->virt;
}