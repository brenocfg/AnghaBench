#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {struct nouveau_dmem_chunk* zone_device_data; } ;
struct nouveau_dmem_chunk {unsigned long pfn_first; TYPE_2__* bo; } ;
struct TYPE_3__ {unsigned long offset; } ;
struct TYPE_4__ {TYPE_1__ bo; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long page_to_pfn (struct page*) ; 

__attribute__((used)) static unsigned long nouveau_dmem_page_addr(struct page *page)
{
	struct nouveau_dmem_chunk *chunk = page->zone_device_data;
	unsigned long idx = page_to_pfn(page) - chunk->pfn_first;

	return (idx << PAGE_SHIFT) + chunk->bo->bo.offset;
}