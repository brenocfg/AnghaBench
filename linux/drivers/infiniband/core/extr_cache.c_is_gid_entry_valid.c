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
struct ib_gid_table_entry {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ GID_TABLE_ENTRY_VALID ; 

__attribute__((used)) static bool is_gid_entry_valid(const struct ib_gid_table_entry *entry)
{
	return entry && entry->state == GID_TABLE_ENTRY_VALID;
}