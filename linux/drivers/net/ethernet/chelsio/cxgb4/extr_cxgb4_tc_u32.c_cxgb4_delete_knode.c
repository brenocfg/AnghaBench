#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int handle; } ;
struct tc_cls_u32_offload {TYPE_1__ knode; } ;
struct net_device {int dummy; } ;
struct cxgb4_tc_u32_table {int size; struct cxgb4_link* table; } ;
struct cxgb4_link {int link_handle; int /*<<< orphan*/  fs; int /*<<< orphan*/ * match_field; int /*<<< orphan*/  tid_map; } ;
struct TYPE_4__ {unsigned int nftids; } ;
struct adapter {TYPE_2__ tids; struct cxgb4_tc_u32_table* tc_u32; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int TC_U32_USERHTID (int) ; 
 int __cxgb4_del_filter (struct net_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_tc_u32_offload (struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int cxgb4_del_filter (struct net_device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

int cxgb4_delete_knode(struct net_device *dev, struct tc_cls_u32_offload *cls)
{
	struct adapter *adapter = netdev2adap(dev);
	unsigned int filter_id, max_tids, i, j;
	struct cxgb4_link *link = NULL;
	struct cxgb4_tc_u32_table *t;
	u32 handle, uhtid;
	int ret;

	if (!can_tc_u32_offload(dev))
		return -EOPNOTSUPP;

	/* Fetch the location to delete the filter. */
	filter_id = cls->knode.handle & 0xFFFFF;

	if (filter_id > adapter->tids.nftids) {
		dev_err(adapter->pdev_dev,
			"Location %d out of range for deletion. Max: %d\n",
			filter_id, adapter->tids.nftids);
		return -ERANGE;
	}

	t = adapter->tc_u32;
	handle = cls->knode.handle;
	uhtid = TC_U32_USERHTID(cls->knode.handle);

	/* Ensure that uhtid is either root u32 (i.e. 0x800)
	 * or a a valid linked bucket.
	 */
	if (uhtid != 0x800 && uhtid >= t->size)
		return -EINVAL;

	/* Delete the specified filter */
	if (uhtid != 0x800) {
		link = &t->table[uhtid - 1];
		if (!link->link_handle)
			return -EINVAL;

		if (!test_bit(filter_id, link->tid_map))
			return -EINVAL;
	}

	ret = cxgb4_del_filter(dev, filter_id, NULL);
	if (ret)
		goto out;

	if (link)
		clear_bit(filter_id, link->tid_map);

	/* If a link is being deleted, then delete all filters
	 * associated with the link.
	 */
	max_tids = adapter->tids.nftids;
	for (i = 0; i < t->size; i++) {
		link = &t->table[i];

		if (link->link_handle == handle) {
			for (j = 0; j < max_tids; j++) {
				if (!test_bit(j, link->tid_map))
					continue;

				ret = __cxgb4_del_filter(dev, j, NULL, NULL);
				if (ret)
					goto out;

				clear_bit(j, link->tid_map);
			}

			/* Clear the link state */
			link->match_field = NULL;
			link->link_handle = 0;
			memset(&link->fs, 0, sizeof(link->fs));
			break;
		}
	}

out:
	return ret;
}