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
struct kset {int dummy; } ;
struct TYPE_3__ {struct kset* kset; scalar_t__ state_in_sysfs; } ;
struct firmware_map_entry {TYPE_1__ kobj; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  firmware_kobj ; 
 scalar_t__ kobject_add (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 struct kset* kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_sysfs_fw_map_entry(struct firmware_map_entry *entry)
{
	static int map_entries_nr;
	static struct kset *mmap_kset;

	if (entry->kobj.state_in_sysfs)
		return -EEXIST;

	if (!mmap_kset) {
		mmap_kset = kset_create_and_add("memmap", NULL, firmware_kobj);
		if (!mmap_kset)
			return -ENOMEM;
	}

	entry->kobj.kset = mmap_kset;
	if (kobject_add(&entry->kobj, NULL, "%d", map_entries_nr++))
		kobject_put(&entry->kobj);

	return 0;
}