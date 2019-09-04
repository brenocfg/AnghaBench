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
struct TYPE_2__ {scalar_t__ mapaddr; } ;
struct mlxsw_pci_queue {TYPE_1__ mem_item; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int MLXSW_PCI_PAGE_SIZE ; 

__attribute__((used)) static dma_addr_t __mlxsw_pci_queue_page_get(struct mlxsw_pci_queue *q,
					     int page_index)
{
	return q->mem_item.mapaddr + MLXSW_PCI_PAGE_SIZE * page_index;
}