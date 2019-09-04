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
 unsigned long PAGE_MASK ; 
 unsigned long const PAGE_SHIFT ; 

__attribute__((used)) static inline int num_user_pages(unsigned long addr,
				 unsigned long len)
{
	const unsigned long spage = addr & PAGE_MASK;
	const unsigned long epage = (addr + len - 1) & PAGE_MASK;

	return 1 + ((epage - spage) >> PAGE_SHIFT);
}