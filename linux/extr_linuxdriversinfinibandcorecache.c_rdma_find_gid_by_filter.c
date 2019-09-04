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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
typedef  struct ib_gid_attr {int /*<<< orphan*/  gid; } const ib_gid_attr ;
struct ib_gid_table_entry {struct ib_gid_attr const attr; } ;
struct ib_gid_table {unsigned int sz; int /*<<< orphan*/  rwlock; struct ib_gid_table_entry** data_vec; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct ib_gid_attr const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gid_entry (struct ib_gid_table_entry*) ; 
 int /*<<< orphan*/  is_gid_entry_valid (struct ib_gid_table_entry*) ; 
 scalar_t__ memcmp (union ib_gid const*,int /*<<< orphan*/ *,int) ; 
 struct ib_gid_table* rdma_gid_table (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

const struct ib_gid_attr *rdma_find_gid_by_filter(
	struct ib_device *ib_dev, const union ib_gid *gid, u8 port,
	bool (*filter)(const union ib_gid *gid, const struct ib_gid_attr *,
		       void *),
	void *context)
{
	const struct ib_gid_attr *res = ERR_PTR(-ENOENT);
	struct ib_gid_table *table;
	unsigned long flags;
	unsigned int i;

	if (!rdma_is_port_valid(ib_dev, port))
		return ERR_PTR(-EINVAL);

	table = rdma_gid_table(ib_dev, port);

	read_lock_irqsave(&table->rwlock, flags);
	for (i = 0; i < table->sz; i++) {
		struct ib_gid_table_entry *entry = table->data_vec[i];

		if (!is_gid_entry_valid(entry))
			continue;

		if (memcmp(gid, &entry->attr.gid, sizeof(*gid)))
			continue;

		if (filter(gid, &entry->attr, context)) {
			get_gid_entry(entry);
			res = &entry->attr;
			break;
		}
	}
	read_unlock_irqrestore(&table->rwlock, flags);
	return res;
}