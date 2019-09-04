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
struct kobject {int /*<<< orphan*/  parent; } ;
struct edac_device_instance {int /*<<< orphan*/  kobj; int /*<<< orphan*/  name; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  kobj; } ;
struct edac_device_block {int nr_attribs; struct kobject kobj; struct edac_dev_sysfs_block_attribute* block_attributes; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct edac_dev_sysfs_block_attribute {TYPE_1__ attr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  edac_dbg (int,char*,struct kobject*,...) ; 
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_block_ctrl ; 
 int /*<<< orphan*/  memset (struct kobject*,int /*<<< orphan*/ ,int) ; 
 int sysfs_create_file (struct kobject*,TYPE_1__*) ; 

__attribute__((used)) static int edac_device_create_block(struct edac_device_ctl_info *edac_dev,
				struct edac_device_instance *instance,
				struct edac_device_block *block)
{
	int i;
	int err;
	struct edac_dev_sysfs_block_attribute *sysfs_attrib;
	struct kobject *main_kobj;

	edac_dbg(4, "Instance '%s' inst_p=%p  block '%s'  block_p=%p\n",
		 instance->name, instance, block->name, block);
	edac_dbg(4, "block kobj=%p  block kobj->parent=%p\n",
		 &block->kobj, &block->kobj.parent);

	/* init this block's kobject */
	memset(&block->kobj, 0, sizeof(struct kobject));

	/* bump the main kobject's reference count for this controller
	 * and this instance is dependent on the main
	 */
	main_kobj = kobject_get(&edac_dev->kobj);
	if (!main_kobj) {
		err = -ENODEV;
		goto err_out;
	}

	/* Add this block's kobject */
	err = kobject_init_and_add(&block->kobj, &ktype_block_ctrl,
				   &instance->kobj,
				   "%s", block->name);
	if (err) {
		edac_dbg(1, "Failed to register instance '%s'\n", block->name);
		kobject_put(main_kobj);
		err = -ENODEV;
		goto err_out;
	}

	/* If there are driver level block attributes, then added them
	 * to the block kobject
	 */
	sysfs_attrib = block->block_attributes;
	if (sysfs_attrib && block->nr_attribs) {
		for (i = 0; i < block->nr_attribs; i++, sysfs_attrib++) {

			edac_dbg(4, "creating block attrib='%s' attrib->%p to kobj=%p\n",
				 sysfs_attrib->attr.name,
				 sysfs_attrib, &block->kobj);

			/* Create each block_attribute file */
			err = sysfs_create_file(&block->kobj,
				&sysfs_attrib->attr);
			if (err)
				goto err_on_attrib;
		}
	}
	kobject_uevent(&block->kobj, KOBJ_ADD);

	return 0;

	/* Error unwind stack */
err_on_attrib:
	kobject_put(&block->kobj);

err_out:
	return err;
}