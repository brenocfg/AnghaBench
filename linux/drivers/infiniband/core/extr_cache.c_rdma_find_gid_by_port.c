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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ib_gid_table {int /*<<< orphan*/  rwlock; TYPE_1__** data_vec; } ;
struct ib_gid_attr {int gid_type; struct net_device* ndev; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;
struct TYPE_2__ {struct ib_gid_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct ib_gid_attr const* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long GID_ATTR_FIND_MASK_GID ; 
 unsigned long GID_ATTR_FIND_MASK_GID_TYPE ; 
 unsigned long GID_ATTR_FIND_MASK_NETDEV ; 
 int find_gid (struct ib_gid_table*,union ib_gid const*,struct ib_gid_attr*,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_gid_entry (TYPE_1__*) ; 
 struct ib_gid_table* rdma_gid_table (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

const struct ib_gid_attr *
rdma_find_gid_by_port(struct ib_device *ib_dev,
		      const union ib_gid *gid,
		      enum ib_gid_type gid_type,
		      u8 port, struct net_device *ndev)
{
	int local_index;
	struct ib_gid_table *table;
	unsigned long mask = GID_ATTR_FIND_MASK_GID |
			     GID_ATTR_FIND_MASK_GID_TYPE;
	struct ib_gid_attr val = {.ndev = ndev, .gid_type = gid_type};
	const struct ib_gid_attr *attr;
	unsigned long flags;

	if (!rdma_is_port_valid(ib_dev, port))
		return ERR_PTR(-ENOENT);

	table = rdma_gid_table(ib_dev, port);

	if (ndev)
		mask |= GID_ATTR_FIND_MASK_NETDEV;

	read_lock_irqsave(&table->rwlock, flags);
	local_index = find_gid(table, gid, &val, false, mask, NULL);
	if (local_index >= 0) {
		get_gid_entry(table->data_vec[local_index]);
		attr = &table->data_vec[local_index]->attr;
		read_unlock_irqrestore(&table->rwlock, flags);
		return attr;
	}

	read_unlock_irqrestore(&table->rwlock, flags);
	return ERR_PTR(-ENOENT);
}