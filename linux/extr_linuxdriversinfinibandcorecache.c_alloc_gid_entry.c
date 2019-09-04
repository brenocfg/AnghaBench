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
struct TYPE_2__ {scalar_t__ ndev; } ;
struct ib_gid_table_entry {int /*<<< orphan*/  state; int /*<<< orphan*/  del_work; TYPE_1__ attr; int /*<<< orphan*/  kref; } ;
struct ib_gid_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GID_TABLE_ENTRY_INVALID ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (scalar_t__) ; 
 int /*<<< orphan*/  free_gid_work ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct ib_gid_table_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct ib_gid_attr const*,int) ; 

__attribute__((used)) static struct ib_gid_table_entry *
alloc_gid_entry(const struct ib_gid_attr *attr)
{
	struct ib_gid_table_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return NULL;
	kref_init(&entry->kref);
	memcpy(&entry->attr, attr, sizeof(*attr));
	if (entry->attr.ndev)
		dev_hold(entry->attr.ndev);
	INIT_WORK(&entry->del_work, free_gid_work);
	entry->state = GID_TABLE_ENTRY_INVALID;
	return entry;
}