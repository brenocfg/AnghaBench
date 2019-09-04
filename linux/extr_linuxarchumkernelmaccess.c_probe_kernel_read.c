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
 long EFAULT ; 
 unsigned long PAGE_SIZE ; 
 long __probe_kernel_read (void*,void const*,size_t) ; 
 scalar_t__ os_mincore (void*,int) ; 
 scalar_t__ rounddown (unsigned long,unsigned long) ; 

long probe_kernel_read(void *dst, const void *src, size_t size)
{
	void *psrc = (void *)rounddown((unsigned long)src, PAGE_SIZE);

	if ((unsigned long)src < PAGE_SIZE || size <= 0)
		return -EFAULT;

	if (os_mincore(psrc, size + src - psrc) <= 0)
		return -EFAULT;

	return __probe_kernel_read(dst, src, size);
}