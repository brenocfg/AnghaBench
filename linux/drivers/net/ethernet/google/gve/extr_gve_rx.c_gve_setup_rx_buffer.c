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
struct page {int dummy; } ;
struct gve_rx_slot_page_info {int /*<<< orphan*/  page_address; scalar_t__ page_offset; struct page* page; } ;
struct gve_rx_data_slot {int /*<<< orphan*/  qpl_offset; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static void gve_setup_rx_buffer(struct gve_rx_slot_page_info *page_info,
				struct gve_rx_data_slot *slot,
				dma_addr_t addr, struct page *page)
{
	page_info->page = page;
	page_info->page_offset = 0;
	page_info->page_address = page_address(page);
	slot->qpl_offset = cpu_to_be64(addr);
}