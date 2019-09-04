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
struct flush_data {unsigned long addr1; unsigned long addr2; struct vm_area_struct* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipi_flush_cache_page ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct flush_data*,int) ; 

void flush_cache_page(struct vm_area_struct *vma,
		     unsigned long address, unsigned long pfn)
{
	struct flush_data fd = {
		.vma = vma,
		.addr1 = address,
		.addr2 = pfn,
	};
	on_each_cpu(ipi_flush_cache_page, &fd, 1);
}