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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct core_table_entry {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_core_table_entry_v0 (struct core_table_entry*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static
void parse_core_table_entry(struct core_table_entry *cte, const u64 read_val, const u8 entry_rev)
{
	switch (entry_rev) {
	case 0:
		parse_core_table_entry_v0(cte, read_val);
		break;
	default:
		cte->type = 0;
		break;
	}
}