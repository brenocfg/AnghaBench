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

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_TLB_SEGSIZE ; 
 int IO_TLB_SHIFT ; 
 int xen_io_tlb_nslabs ; 

__attribute__((used)) static unsigned long xen_set_nslabs(unsigned long nr_tbl)
{
	if (!nr_tbl) {
		xen_io_tlb_nslabs = (64 * 1024 * 1024 >> IO_TLB_SHIFT);
		xen_io_tlb_nslabs = ALIGN(xen_io_tlb_nslabs, IO_TLB_SEGSIZE);
	} else
		xen_io_tlb_nslabs = nr_tbl;

	return xen_io_tlb_nslabs << IO_TLB_SHIFT;
}