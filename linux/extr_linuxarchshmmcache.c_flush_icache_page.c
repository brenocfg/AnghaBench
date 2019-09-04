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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cacheop_on_each_cpu (int /*<<< orphan*/ ,struct page*,int) ; 
 int /*<<< orphan*/  local_flush_icache_page ; 

void flush_icache_page(struct vm_area_struct *vma, struct page *page)
{
	/* Nothing uses the VMA, so just pass the struct page along */
	cacheop_on_each_cpu(local_flush_icache_page, page, 1);
}