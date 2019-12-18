#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ib_gid_table {int sz; int /*<<< orphan*/  rwlock; TYPE_1__** data_vec; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {struct ib_gid_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_gid_attr const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gid_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  is_gid_entry_valid (TYPE_1__*) ; 
 struct ib_gid_table* rdma_gid_table (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

const struct ib_gid_attr *
rdma_get_gid_attr(struct ib_device *device, u8 port_num, int index)
{
	const struct ib_gid_attr *attr = ERR_PTR(-EINVAL);
	struct ib_gid_table *table;
	unsigned long flags;

	if (!rdma_is_port_valid(device, port_num))
		return ERR_PTR(-EINVAL);

	table = rdma_gid_table(device, port_num);
	if (index < 0 || index >= table->sz)
		return ERR_PTR(-EINVAL);

	read_lock_irqsave(&table->rwlock, flags);
	if (!is_gid_entry_valid(table->data_vec[index]))
		goto done;

	get_gid_entry(table->data_vec[index]);
	attr = &table->data_vec[index]->attr;
done:
	read_unlock_irqrestore(&table->rwlock, flags);
	return attr;
}