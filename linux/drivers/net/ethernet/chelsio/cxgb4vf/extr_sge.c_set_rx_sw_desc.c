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
struct rx_sw_desc {int /*<<< orphan*/  dma_addr; struct page* page; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline void set_rx_sw_desc(struct rx_sw_desc *sdesc, struct page *page,
				  dma_addr_t dma_addr)
{
	sdesc->page = page;
	sdesc->dma_addr = dma_addr;
}