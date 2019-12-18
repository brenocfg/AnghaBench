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
struct nvme_ns_ids {int dummy; } ;
struct nvme_ns {TYPE_1__* head; int /*<<< orphan*/  flags; struct nvme_ctrl* ctrl; } ;
struct nvme_id_ns {scalar_t__ ncap; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; } ;
struct gendisk {struct nvme_ns* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns_id; int /*<<< orphan*/  ids; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NVME_NS_DEAD ; 
 int NVME_SC_DNR ; 
 int /*<<< orphan*/  __nvme_revalidate_disk (struct gendisk*,struct nvme_id_ns*) ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_id_ns*) ; 
 int /*<<< orphan*/  nvme_error_status (int) ; 
 int nvme_identify_ns (struct nvme_ctrl*,int /*<<< orphan*/ ,struct nvme_id_ns**) ; 
 int /*<<< orphan*/  nvme_ns_ids_equal (int /*<<< orphan*/ *,struct nvme_ns_ids*) ; 
 int nvme_report_ns_ids (struct nvme_ctrl*,int /*<<< orphan*/ ,struct nvme_id_ns*,struct nvme_ns_ids*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_revalidate_disk(struct gendisk *disk)
{
	struct nvme_ns *ns = disk->private_data;
	struct nvme_ctrl *ctrl = ns->ctrl;
	struct nvme_id_ns *id;
	struct nvme_ns_ids ids;
	int ret = 0;

	if (test_bit(NVME_NS_DEAD, &ns->flags)) {
		set_capacity(disk, 0);
		return -ENODEV;
	}

	ret = nvme_identify_ns(ctrl, ns->head->ns_id, &id);
	if (ret)
		goto out;

	if (id->ncap == 0) {
		ret = -ENODEV;
		goto free_id;
	}

	__nvme_revalidate_disk(disk, id);
	ret = nvme_report_ns_ids(ctrl, ns->head->ns_id, id, &ids);
	if (ret)
		goto free_id;

	if (!nvme_ns_ids_equal(&ns->head->ids, &ids)) {
		dev_err(ctrl->device,
			"identifiers changed for nsid %d\n", ns->head->ns_id);
		ret = -ENODEV;
	}

free_id:
	kfree(id);
out:
	/*
	 * Only fail the function if we got a fatal error back from the
	 * device, otherwise ignore the error and just move on.
	 */
	if (ret == -ENOMEM || (ret > 0 && !(ret & NVME_SC_DNR)))
		ret = 0;
	else if (ret > 0)
		ret = blk_status_to_errno(nvme_error_status(ret));
	return ret;
}