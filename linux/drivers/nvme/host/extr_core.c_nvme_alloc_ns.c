#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {int lba_shift; scalar_t__ ncap; int* vs; TYPE_5__* queue; int /*<<< orphan*/  head; int /*<<< orphan*/  siblings; struct gendisk* disk; int /*<<< orphan*/  fault_inject; int /*<<< orphan*/  list; int /*<<< orphan*/  kref; struct nvme_ctrl* ctrl; } ;
struct nvme_id_ns {int lba_shift; scalar_t__ ncap; int* vs; TYPE_5__* queue; int /*<<< orphan*/  head; int /*<<< orphan*/  siblings; struct gendisk* disk; int /*<<< orphan*/  fault_inject; int /*<<< orphan*/  list; int /*<<< orphan*/  kref; struct nvme_ctrl* ctrl; } ;
struct nvme_ctrl {int numa_node; int quirks; TYPE_4__* subsys; int /*<<< orphan*/  device; int /*<<< orphan*/  namespaces_rwsem; int /*<<< orphan*/  namespaces; TYPE_3__* ops; TYPE_1__* opts; int /*<<< orphan*/  tagset; } ;
struct gendisk {int flags; int /*<<< orphan*/  disk_name; TYPE_5__* queue; struct nvme_ns* private_data; int /*<<< orphan*/ * fops; } ;
struct TYPE_16__ {struct nvme_ns* queuedata; TYPE_2__* backing_dev_info; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  capabilities; } ;
struct TYPE_12__ {scalar_t__ data_digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_STABLE_WRITES ; 
 int DISK_NAME_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 int NVME_F_PCI_P2PDMA ; 
 int NVME_QUIRK_LIGHTNVM ; 
 int PTR_ERR (TYPE_5__*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  QUEUE_FLAG_PCI_P2PDMA ; 
 int /*<<< orphan*/  __nvme_revalidate_disk (struct gendisk*,struct nvme_ns*) ; 
 struct gendisk* alloc_disk_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_5__*) ; 
 TYPE_5__* blk_mq_init_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_5__*,int) ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_add_disk (int /*<<< orphan*/ ,struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_ns*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvme_ns* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_error_status (int) ; 
 int /*<<< orphan*/  nvme_fault_inject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_fops ; 
 int /*<<< orphan*/  nvme_get_ctrl (struct nvme_ctrl*) ; 
 int nvme_identify_ns (struct nvme_ctrl*,unsigned int,struct nvme_ns**) ; 
 int nvme_init_ns_head (struct nvme_ns*,unsigned int,struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_mpath_add_disk (struct nvme_ns*,struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_ns_id_attr_groups ; 
 int nvme_nvm_register (struct nvme_ns*,char*,int) ; 
 int /*<<< orphan*/  nvme_put_ns_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_set_disk_name (char*,struct nvme_ns*,struct nvme_ctrl*,int*) ; 
 int /*<<< orphan*/  nvme_set_queue_limits (struct nvme_ctrl*,TYPE_5__*) ; 
 int /*<<< orphan*/  nvme_setup_streams_ns (struct nvme_ctrl*,struct nvme_ns*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_alloc_ns(struct nvme_ctrl *ctrl, unsigned nsid)
{
	struct nvme_ns *ns;
	struct gendisk *disk;
	struct nvme_id_ns *id;
	char disk_name[DISK_NAME_LEN];
	int node = ctrl->numa_node, flags = GENHD_FL_EXT_DEVT, ret;

	ns = kzalloc_node(sizeof(*ns), GFP_KERNEL, node);
	if (!ns)
		return -ENOMEM;

	ns->queue = blk_mq_init_queue(ctrl->tagset);
	if (IS_ERR(ns->queue)) {
		ret = PTR_ERR(ns->queue);
		goto out_free_ns;
	}

	if (ctrl->opts && ctrl->opts->data_digest)
		ns->queue->backing_dev_info->capabilities
			|= BDI_CAP_STABLE_WRITES;

	blk_queue_flag_set(QUEUE_FLAG_NONROT, ns->queue);
	if (ctrl->ops->flags & NVME_F_PCI_P2PDMA)
		blk_queue_flag_set(QUEUE_FLAG_PCI_P2PDMA, ns->queue);

	ns->queue->queuedata = ns;
	ns->ctrl = ctrl;

	kref_init(&ns->kref);
	ns->lba_shift = 9; /* set to a default value for 512 until disk is validated */

	blk_queue_logical_block_size(ns->queue, 1 << ns->lba_shift);
	nvme_set_queue_limits(ctrl, ns->queue);

	ret = nvme_identify_ns(ctrl, nsid, &id);
	if (ret)
		goto out_free_queue;

	if (id->ncap == 0) {
		ret = -EINVAL;
		goto out_free_id;
	}

	ret = nvme_init_ns_head(ns, nsid, id);
	if (ret)
		goto out_free_id;
	nvme_setup_streams_ns(ctrl, ns);
	nvme_set_disk_name(disk_name, ns, ctrl, &flags);

	disk = alloc_disk_node(0, node);
	if (!disk) {
		ret = -ENOMEM;
		goto out_unlink_ns;
	}

	disk->fops = &nvme_fops;
	disk->private_data = ns;
	disk->queue = ns->queue;
	disk->flags = flags;
	memcpy(disk->disk_name, disk_name, DISK_NAME_LEN);
	ns->disk = disk;

	__nvme_revalidate_disk(disk, id);

	if ((ctrl->quirks & NVME_QUIRK_LIGHTNVM) && id->vs[0] == 0x1) {
		ret = nvme_nvm_register(ns, disk_name, node);
		if (ret) {
			dev_warn(ctrl->device, "LightNVM init failure\n");
			goto out_put_disk;
		}
	}

	down_write(&ctrl->namespaces_rwsem);
	list_add_tail(&ns->list, &ctrl->namespaces);
	up_write(&ctrl->namespaces_rwsem);

	nvme_get_ctrl(ctrl);

	device_add_disk(ctrl->device, ns->disk, nvme_ns_id_attr_groups);

	nvme_mpath_add_disk(ns, id);
	nvme_fault_inject_init(&ns->fault_inject, ns->disk->disk_name);
	kfree(id);

	return 0;
 out_put_disk:
	put_disk(ns->disk);
 out_unlink_ns:
	mutex_lock(&ctrl->subsys->lock);
	list_del_rcu(&ns->siblings);
	mutex_unlock(&ctrl->subsys->lock);
	nvme_put_ns_head(ns->head);
 out_free_id:
	kfree(id);
 out_free_queue:
	blk_cleanup_queue(ns->queue);
 out_free_ns:
	kfree(ns);
	if (ret > 0)
		ret = blk_status_to_errno(nvme_error_status(ret));
	return ret;
}