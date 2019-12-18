#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct TYPE_2__ {int total_entries; } ;
struct gasket_page_table {TYPE_1__ config; } ;

/* Variables and functions */
 int GASKET_SIMPLE_PAGE_SHIFT ; 

__attribute__((used)) static int gasket_simple_page_idx(struct gasket_page_table *pg_tbl,
				  ulong dev_addr)
{
	return (dev_addr >> GASKET_SIMPLE_PAGE_SHIFT) &
		(pg_tbl->config.total_entries - 1);
}