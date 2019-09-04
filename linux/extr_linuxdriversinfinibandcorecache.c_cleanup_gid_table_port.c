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
typedef  int /*<<< orphan*/  u8 ;
struct ib_gid_table {int sz; int /*<<< orphan*/  lock; int /*<<< orphan*/ * data_vec; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gid (struct ib_device*,int /*<<< orphan*/ ,struct ib_gid_table*,int) ; 
 int /*<<< orphan*/  dispatch_gid_change_event (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gid_entry_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_gid_table_port(struct ib_device *ib_dev, u8 port,
				   struct ib_gid_table *table)
{
	int i;
	bool deleted = false;

	if (!table)
		return;

	mutex_lock(&table->lock);
	for (i = 0; i < table->sz; ++i) {
		if (is_gid_entry_valid(table->data_vec[i])) {
			del_gid(ib_dev, port, table, i);
			deleted = true;
		}
	}
	mutex_unlock(&table->lock);

	if (deleted)
		dispatch_gid_change_event(ib_dev, port);
}