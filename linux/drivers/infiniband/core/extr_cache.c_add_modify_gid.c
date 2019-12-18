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
struct ib_gid_table_entry {int dummy; } ;
struct ib_gid_table {int /*<<< orphan*/ * data_vec; } ;
struct ib_gid_attr {size_t index; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int add_roce_gid (struct ib_gid_table_entry*) ; 
 struct ib_gid_table_entry* alloc_gid_entry (struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  del_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_gid_table*,size_t) ; 
 scalar_t__ is_gid_entry_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_gid_entry (struct ib_gid_table_entry*) ; 
 scalar_t__ rdma_is_zero_gid (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_protocol_roce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_gid_entry (struct ib_gid_table*,struct ib_gid_table_entry*) ; 

__attribute__((used)) static int add_modify_gid(struct ib_gid_table *table,
			  const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry;
	int ret = 0;

	/*
	 * Invalidate any old entry in the table to make it safe to write to
	 * this index.
	 */
	if (is_gid_entry_valid(table->data_vec[attr->index]))
		del_gid(attr->device, attr->port_num, table, attr->index);

	/*
	 * Some HCA's report multiple GID entries with only one valid GID, and
	 * leave other unused entries as the zero GID. Convert zero GIDs to
	 * empty table entries instead of storing them.
	 */
	if (rdma_is_zero_gid(&attr->gid))
		return 0;

	entry = alloc_gid_entry(attr);
	if (!entry)
		return -ENOMEM;

	if (rdma_protocol_roce(attr->device, attr->port_num)) {
		ret = add_roce_gid(entry);
		if (ret)
			goto done;
	}

	store_gid_entry(table, entry);
	return 0;

done:
	put_gid_entry(entry);
	return ret;
}