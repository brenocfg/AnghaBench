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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int __map_kernel_page (unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int radix__map_kernel_page(unsigned long ea, unsigned long pa,
			  pgprot_t flags,
			  unsigned int map_page_size)
{
	return __map_kernel_page(ea, pa, flags, map_page_size, -1, 0, 0);
}