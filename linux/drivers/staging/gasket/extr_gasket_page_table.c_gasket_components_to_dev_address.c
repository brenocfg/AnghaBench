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
typedef  int uint ;
struct gasket_page_table {int extended_flag; } ;

/* Variables and functions */
 int GASKET_SIMPLE_PAGE_SHIFT ; 

__attribute__((used)) static ulong gasket_components_to_dev_address(struct gasket_page_table *pg_tbl,
					      int is_simple, uint page_index,
					      uint offset)
{
	ulong dev_addr = (page_index << GASKET_SIMPLE_PAGE_SHIFT) | offset;

	return is_simple ? dev_addr : (pg_tbl->extended_flag | dev_addr);
}