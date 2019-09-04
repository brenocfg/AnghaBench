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
 unsigned long* ia64_rse_rnat_addr (unsigned long*) ; 

__attribute__((used)) static inline int
on_kernel_rbs (unsigned long addr, unsigned long bspstore,
	       unsigned long urbs_end)
{
	unsigned long *rnat_addr = ia64_rse_rnat_addr((unsigned long *)
						      urbs_end);
	return (addr >= bspstore && addr <= (unsigned long) rnat_addr);
}