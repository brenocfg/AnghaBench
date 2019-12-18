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
typedef  scalar_t__ u32 ;
struct ena_host_attribute {scalar_t__ debug_area_size; int /*<<< orphan*/  debug_area_virt_addr; int /*<<< orphan*/  debug_area_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_host_attribute host_attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_allocate_debug_area(struct ena_com_dev *ena_dev,
				u32 debug_area_size)
{
	struct ena_host_attribute *host_attr = &ena_dev->host_attr;

	host_attr->debug_area_virt_addr =
		dma_alloc_coherent(ena_dev->dmadev, debug_area_size,
				   &host_attr->debug_area_dma_addr,
				   GFP_KERNEL);
	if (unlikely(!host_attr->debug_area_virt_addr)) {
		host_attr->debug_area_size = 0;
		return -ENOMEM;
	}

	host_attr->debug_area_size = debug_area_size;

	return 0;
}