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
struct ib_gid_table {int /*<<< orphan*/  lock; } ;
struct ib_gid_attr {int index; int /*<<< orphan*/  gid; int /*<<< orphan*/  port_num; struct ib_device* device; } ;
struct ib_device {int (* query_gid ) (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_modify_gid (struct ib_gid_table*,struct ib_gid_attr*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ,int) ; 
 struct ib_gid_table* rdma_gid_table (struct ib_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_non_roce_gid_cache(struct ib_device *device,
				     u8 port, int gid_tbl_len)
{
	struct ib_gid_attr gid_attr = {};
	struct ib_gid_table *table;
	int ret = 0;
	int i;

	gid_attr.device = device;
	gid_attr.port_num = port;
	table = rdma_gid_table(device, port);

	mutex_lock(&table->lock);
	for (i = 0; i < gid_tbl_len; ++i) {
		if (!device->query_gid)
			continue;
		ret = device->query_gid(device, port, i, &gid_attr.gid);
		if (ret) {
			pr_warn("query_gid failed (%d) for %s (index %d)\n",
				ret, device->name, i);
			goto err;
		}
		gid_attr.index = i;
		add_modify_gid(table, &gid_attr);
	}
err:
	mutex_unlock(&table->lock);
	return ret;
}