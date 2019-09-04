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
struct edac_device_instance {int name; int nr_blocks; struct kobject kobj; int /*<<< orphan*/ * blocks; struct edac_device_ctl_info* ctl; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  kobj; struct edac_device_instance* instances; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,...) ; 
 int edac_device_create_block (struct edac_device_ctl_info*,struct edac_device_instance*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_device_delete_block (struct edac_device_ctl_info*,int /*<<< orphan*/ *) ; 
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_instance_ctrl ; 
 int /*<<< orphan*/  memset (struct kobject*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int edac_device_create_instance(struct edac_device_ctl_info *edac_dev,
				int idx)
{
	int i, j;
	int err;
	struct edac_device_instance *instance;
	struct kobject *main_kobj;

	instance = &edac_dev->instances[idx];

	/* Init the instance's kobject */
	memset(&instance->kobj, 0, sizeof(struct kobject));

	instance->ctl = edac_dev;

	/* bump the main kobject's reference count for this controller
	 * and this instance is dependent on the main
	 */
	main_kobj = kobject_get(&edac_dev->kobj);
	if (!main_kobj) {
		err = -ENODEV;
		goto err_out;
	}

	/* Formally register this instance's kobject under the edac_device */
	err = kobject_init_and_add(&instance->kobj, &ktype_instance_ctrl,
				   &edac_dev->kobj, "%s", instance->name);
	if (err != 0) {
		edac_dbg(2, "Failed to register instance '%s'\n",
			 instance->name);
		kobject_put(main_kobj);
		goto err_out;
	}

	edac_dbg(4, "now register '%d' blocks for instance %d\n",
		 instance->nr_blocks, idx);

	/* register all blocks of this instance */
	for (i = 0; i < instance->nr_blocks; i++) {
		err = edac_device_create_block(edac_dev, instance,
						&instance->blocks[i]);
		if (err) {
			/* If any fail, remove all previous ones */
			for (j = 0; j < i; j++)
				edac_device_delete_block(edac_dev,
							&instance->blocks[j]);
			goto err_release_instance_kobj;
		}
	}
	kobject_uevent(&instance->kobj, KOBJ_ADD);

	edac_dbg(4, "Registered instance %d '%s' kobject\n",
		 idx, instance->name);

	return 0;

	/* error unwind stack */
err_release_instance_kobj:
	kobject_put(&instance->kobj);

err_out:
	return err;
}