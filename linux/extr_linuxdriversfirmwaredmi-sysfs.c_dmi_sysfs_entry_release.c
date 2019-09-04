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
struct kobject {int dummy; } ;
struct dmi_sysfs_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  entry_list_lock ; 
 int /*<<< orphan*/  kfree (struct dmi_sysfs_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct dmi_sysfs_entry* to_entry (struct kobject*) ; 

__attribute__((used)) static void dmi_sysfs_entry_release(struct kobject *kobj)
{
	struct dmi_sysfs_entry *entry = to_entry(kobj);

	spin_lock(&entry_list_lock);
	list_del(&entry->list);
	spin_unlock(&entry_list_lock);
	kfree(entry);
}