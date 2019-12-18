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
struct net_device {int dummy; } ;
struct ib_gid_table_entry {int /*<<< orphan*/  state; int /*<<< orphan*/  del_work; int /*<<< orphan*/  attr; int /*<<< orphan*/  kref; TYPE_1__* ndev_storage; } ;
struct ib_gid_attr {int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GID_TABLE_ENTRY_INVALID ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  free_gid_work ; 
 int /*<<< orphan*/  kfree (struct ib_gid_table_entry*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ib_gid_attr const*,int) ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ib_gid_table_entry *
alloc_gid_entry(const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry;
	struct net_device *ndev;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return NULL;

	ndev = rcu_dereference_protected(attr->ndev, 1);
	if (ndev) {
		entry->ndev_storage = kzalloc(sizeof(*entry->ndev_storage),
					      GFP_KERNEL);
		if (!entry->ndev_storage) {
			kfree(entry);
			return NULL;
		}
		dev_hold(ndev);
		entry->ndev_storage->ndev = ndev;
	}
	kref_init(&entry->kref);
	memcpy(&entry->attr, attr, sizeof(*attr));
	INIT_WORK(&entry->del_work, free_gid_work);
	entry->state = GID_TABLE_ENTRY_INVALID;
	return entry;
}