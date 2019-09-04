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
 unsigned long SLB_VSID_SSIZE_SHIFT ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long slb_vsid_shift (int) ; 

__attribute__((used)) static inline unsigned long mk_vsid_data(unsigned long ea, int ssize,
					 unsigned long flags)
{
	return (get_kernel_vsid(ea, ssize) << slb_vsid_shift(ssize)) | flags |
		((unsigned long) ssize << SLB_VSID_SSIZE_SHIFT);
}