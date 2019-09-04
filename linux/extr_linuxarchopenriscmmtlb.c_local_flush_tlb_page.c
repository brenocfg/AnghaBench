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

/* Variables and functions */
 int /*<<< orphan*/  flush_dtlb_page_eir (unsigned long) ; 
 int /*<<< orphan*/  flush_dtlb_page_no_eir (unsigned long) ; 
 int /*<<< orphan*/  flush_itlb_page_eir (unsigned long) ; 
 int /*<<< orphan*/  flush_itlb_page_no_eir (unsigned long) ; 
 scalar_t__ have_dtlbeir ; 
 scalar_t__ have_itlbeir ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long addr)
{
	if (have_dtlbeir)
		flush_dtlb_page_eir(addr);
	else
		flush_dtlb_page_no_eir(addr);

	if (have_itlbeir)
		flush_itlb_page_eir(addr);
	else
		flush_itlb_page_no_eir(addr);
}