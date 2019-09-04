#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * kset; } ;
struct efi_runtime_map_entry {TYPE_1__ kobj; int /*<<< orphan*/  md; } ;
typedef  int /*<<< orphan*/  efi_memory_desc_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct efi_runtime_map_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int kobject_add (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 int /*<<< orphan*/ * kset_create_and_add (char*,int /*<<< orphan*/ *,struct kobject*) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 struct efi_runtime_map_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_kset ; 
 int /*<<< orphan*/  map_ktype ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct efi_runtime_map_entry *
add_sysfs_runtime_map_entry(struct kobject *kobj, int nr,
			    efi_memory_desc_t *md)
{
	int ret;
	struct efi_runtime_map_entry *entry;

	if (!map_kset) {
		map_kset = kset_create_and_add("runtime-map", NULL, kobj);
		if (!map_kset)
			return ERR_PTR(-ENOMEM);
	}

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		kset_unregister(map_kset);
		map_kset = NULL;
		return ERR_PTR(-ENOMEM);
	}

	memcpy(&entry->md, md, sizeof(efi_memory_desc_t));

	kobject_init(&entry->kobj, &map_ktype);
	entry->kobj.kset = map_kset;
	ret = kobject_add(&entry->kobj, NULL, "%d", nr);
	if (ret) {
		kobject_put(&entry->kobj);
		kset_unregister(map_kset);
		map_kset = NULL;
		return ERR_PTR(ret);
	}

	return entry;
}