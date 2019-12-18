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
typedef  int ulong ;
struct gasket_page_table {int dummy; } ;

/* Variables and functions */
 int GASKET_EXTENDED_LVL1_SHIFT ; 
 int GASKET_PAGES_PER_SUBTABLE ; 

__attribute__((used)) static ulong gasket_extended_lvl1_page_idx(struct gasket_page_table *pg_tbl,
					   ulong dev_addr)
{
	return (dev_addr >> GASKET_EXTENDED_LVL1_SHIFT) &
	       (GASKET_PAGES_PER_SUBTABLE - 1);
}