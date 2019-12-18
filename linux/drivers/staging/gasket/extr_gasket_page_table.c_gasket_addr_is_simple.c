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
typedef  int /*<<< orphan*/  ulong ;
struct gasket_page_table {int /*<<< orphan*/  extended_flag; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */

__attribute__((used)) static inline bool gasket_addr_is_simple(struct gasket_page_table *pg_tbl,
					 ulong addr)
{
	return !((addr) & (pg_tbl)->extended_flag);
}