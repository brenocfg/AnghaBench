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
struct ib_gid_table_entry {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_gid_entry ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_gid_entry_locked(struct ib_gid_table_entry *entry)
{
	kref_put(&entry->kref, free_gid_entry);
}