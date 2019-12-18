#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/  class; } ;
struct nvme_subsystem {int instance; int /*<<< orphan*/  ctrls; TYPE_1__ dev; int /*<<< orphan*/  entry; int /*<<< orphan*/  ns_ida; int /*<<< orphan*/  subnqn; int /*<<< orphan*/  iopolicy; void* awupf; int /*<<< orphan*/  cmic; void* vendor_id; int /*<<< orphan*/  firmware_rev; int /*<<< orphan*/  model; int /*<<< orphan*/  serial; int /*<<< orphan*/  nsheads; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;
struct nvme_id_ctrl {int /*<<< orphan*/  awupf; int /*<<< orphan*/  cmic; int /*<<< orphan*/  vid; int /*<<< orphan*/  fr; int /*<<< orphan*/  mn; int /*<<< orphan*/  sn; } ;
struct nvme_ctrl {int instance; int /*<<< orphan*/  subsys_entry; struct nvme_subsystem* subsys; TYPE_5__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVME_IOPOLICY_NUMA ; 
 struct nvme_subsystem* __nvme_find_get_subsystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvme_subsystem* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_init_subnqn (struct nvme_subsystem*,struct nvme_ctrl*,struct nvme_id_ctrl*) ; 
 int /*<<< orphan*/  nvme_put_subsystem (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  nvme_release_subsystem ; 
 int /*<<< orphan*/  nvme_subsys_attrs_groups ; 
 int /*<<< orphan*/  nvme_subsys_class ; 
 int /*<<< orphan*/  nvme_subsystems ; 
 int /*<<< orphan*/  nvme_subsystems_lock ; 
 int /*<<< orphan*/  nvme_validate_cntlid (struct nvme_subsystem*,struct nvme_ctrl*,struct nvme_id_ctrl*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_init_subsystem(struct nvme_ctrl *ctrl, struct nvme_id_ctrl *id)
{
	struct nvme_subsystem *subsys, *found;
	int ret;

	subsys = kzalloc(sizeof(*subsys), GFP_KERNEL);
	if (!subsys)
		return -ENOMEM;

	subsys->instance = -1;
	mutex_init(&subsys->lock);
	kref_init(&subsys->ref);
	INIT_LIST_HEAD(&subsys->ctrls);
	INIT_LIST_HEAD(&subsys->nsheads);
	nvme_init_subnqn(subsys, ctrl, id);
	memcpy(subsys->serial, id->sn, sizeof(subsys->serial));
	memcpy(subsys->model, id->mn, sizeof(subsys->model));
	memcpy(subsys->firmware_rev, id->fr, sizeof(subsys->firmware_rev));
	subsys->vendor_id = le16_to_cpu(id->vid);
	subsys->cmic = id->cmic;
	subsys->awupf = le16_to_cpu(id->awupf);
#ifdef CONFIG_NVME_MULTIPATH
	subsys->iopolicy = NVME_IOPOLICY_NUMA;
#endif

	subsys->dev.class = nvme_subsys_class;
	subsys->dev.release = nvme_release_subsystem;
	subsys->dev.groups = nvme_subsys_attrs_groups;
	dev_set_name(&subsys->dev, "nvme-subsys%d", ctrl->instance);
	device_initialize(&subsys->dev);

	mutex_lock(&nvme_subsystems_lock);
	found = __nvme_find_get_subsystem(subsys->subnqn);
	if (found) {
		put_device(&subsys->dev);
		subsys = found;

		if (!nvme_validate_cntlid(subsys, ctrl, id)) {
			ret = -EINVAL;
			goto out_put_subsystem;
		}
	} else {
		ret = device_add(&subsys->dev);
		if (ret) {
			dev_err(ctrl->device,
				"failed to register subsystem device.\n");
			put_device(&subsys->dev);
			goto out_unlock;
		}
		ida_init(&subsys->ns_ida);
		list_add_tail(&subsys->entry, &nvme_subsystems);
	}

	ret = sysfs_create_link(&subsys->dev.kobj, &ctrl->device->kobj,
				dev_name(ctrl->device));
	if (ret) {
		dev_err(ctrl->device,
			"failed to create sysfs link from subsystem.\n");
		goto out_put_subsystem;
	}

	if (!found)
		subsys->instance = ctrl->instance;
	ctrl->subsys = subsys;
	list_add_tail(&ctrl->subsys_entry, &subsys->ctrls);
	mutex_unlock(&nvme_subsystems_lock);
	return 0;

out_put_subsystem:
	nvme_put_subsystem(subsys);
out_unlock:
	mutex_unlock(&nvme_subsystems_lock);
	return ret;
}