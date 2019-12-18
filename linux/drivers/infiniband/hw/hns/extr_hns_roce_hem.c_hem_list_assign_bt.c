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
typedef  scalar_t__ u64 ;
struct roce_hem_item {scalar_t__ dma_addr; void* addr; } ;
struct hns_roce_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static void hem_list_assign_bt(struct hns_roce_dev *hr_dev,
			       struct roce_hem_item *hem, void *cpu_addr,
			       u64 phy_addr)
{
	hem->addr = cpu_addr;
	hem->dma_addr = (dma_addr_t)phy_addr;
}