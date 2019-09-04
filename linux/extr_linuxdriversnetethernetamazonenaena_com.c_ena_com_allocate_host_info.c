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
struct ena_host_attribute {int /*<<< orphan*/  host_info; int /*<<< orphan*/  host_info_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_host_attribute host_attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dma_zalloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_allocate_host_info(struct ena_com_dev *ena_dev)
{
	struct ena_host_attribute *host_attr = &ena_dev->host_attr;

	host_attr->host_info =
		dma_zalloc_coherent(ena_dev->dmadev, SZ_4K,
				    &host_attr->host_info_dma_addr, GFP_KERNEL);
	if (unlikely(!host_attr->host_info))
		return -ENOMEM;

	return 0;
}