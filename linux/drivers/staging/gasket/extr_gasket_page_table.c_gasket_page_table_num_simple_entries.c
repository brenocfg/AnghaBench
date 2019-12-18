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
typedef  int /*<<< orphan*/  uint ;
struct gasket_page_table {int /*<<< orphan*/  num_simple_entries; } ;

/* Variables and functions */

uint gasket_page_table_num_simple_entries(struct gasket_page_table *pg_tbl)
{
	if (!pg_tbl)
		return 0;
	return pg_tbl->num_simple_entries;
}