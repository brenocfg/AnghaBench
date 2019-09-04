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
 long EINVAL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 long ksys_mmap_pgoff (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

long old_mmap(unsigned long addr, unsigned long len,
	      unsigned long prot, unsigned long flags,
	      unsigned long fd, unsigned long offset)
{
	long err = -EINVAL;
	if (offset & ~PAGE_MASK)
		goto out;

	err = ksys_mmap_pgoff(addr, len, prot, flags, fd, offset >> PAGE_SHIFT);
 out:
	return err;
}