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
struct root_entry {int hi; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int VTD_PAGE_MASK ; 

__attribute__((used)) static phys_addr_t root_entry_uctp(struct root_entry *re)
{
	if (!(re->hi & 1))
		return 0;

	return re->hi & VTD_PAGE_MASK;
}