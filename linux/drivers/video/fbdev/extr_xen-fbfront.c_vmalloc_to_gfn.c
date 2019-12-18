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
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 
 unsigned long xen_page_to_gfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vmalloc_to_gfn(void *address)
{
	return xen_page_to_gfn(vmalloc_to_page(address));
}