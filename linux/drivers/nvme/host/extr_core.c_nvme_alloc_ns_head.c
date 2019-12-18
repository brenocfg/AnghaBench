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
struct nvme_ns_head {int instance; unsigned int ns_id; int /*<<< orphan*/  srcu; int /*<<< orphan*/  entry; int /*<<< orphan*/  ids; int /*<<< orphan*/  ref; TYPE_1__* subsys; int /*<<< orphan*/  list; } ;
struct nvme_ns {int dummy; } ;
struct nvme_id_ns {int dummy; } ;
struct nvme_ctrl {TYPE_1__* subsys; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns_ida; int /*<<< orphan*/  ref; int /*<<< orphan*/  nsheads; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nvme_ns_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __nvme_check_ids (TYPE_1__*,struct nvme_ns_head*) ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_ns_head*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvme_ns_head* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int num_possible_nodes () ; 
 int /*<<< orphan*/  nvme_error_status (int) ; 
 int nvme_mpath_alloc_disk (struct nvme_ctrl*,struct nvme_ns_head*) ; 
 int nvme_report_ns_ids (struct nvme_ctrl*,unsigned int,struct nvme_id_ns*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nvme_ns_head *nvme_alloc_ns_head(struct nvme_ctrl *ctrl,
		unsigned nsid, struct nvme_id_ns *id)
{
	struct nvme_ns_head *head;
	size_t size = sizeof(*head);
	int ret = -ENOMEM;

#ifdef CONFIG_NVME_MULTIPATH
	size += num_possible_nodes() * sizeof(struct nvme_ns *);
#endif

	head = kzalloc(size, GFP_KERNEL);
	if (!head)
		goto out;
	ret = ida_simple_get(&ctrl->subsys->ns_ida, 1, 0, GFP_KERNEL);
	if (ret < 0)
		goto out_free_head;
	head->instance = ret;
	INIT_LIST_HEAD(&head->list);
	ret = init_srcu_struct(&head->srcu);
	if (ret)
		goto out_ida_remove;
	head->subsys = ctrl->subsys;
	head->ns_id = nsid;
	kref_init(&head->ref);

	ret = nvme_report_ns_ids(ctrl, nsid, id, &head->ids);
	if (ret)
		goto out_cleanup_srcu;

	ret = __nvme_check_ids(ctrl->subsys, head);
	if (ret) {
		dev_err(ctrl->device,
			"duplicate IDs for nsid %d\n", nsid);
		goto out_cleanup_srcu;
	}

	ret = nvme_mpath_alloc_disk(ctrl, head);
	if (ret)
		goto out_cleanup_srcu;

	list_add_tail(&head->entry, &ctrl->subsys->nsheads);

	kref_get(&ctrl->subsys->ref);

	return head;
out_cleanup_srcu:
	cleanup_srcu_struct(&head->srcu);
out_ida_remove:
	ida_simple_remove(&ctrl->subsys->ns_ida, head->instance);
out_free_head:
	kfree(head);
out:
	if (ret > 0)
		ret = blk_status_to_errno(nvme_error_status(ret));
	return ERR_PTR(ret);
}