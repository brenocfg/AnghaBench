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
struct nvme_ctrl {void* admin_tagset; void* fabrics_q; void* admin_q; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  blk_cleanup_queue (void*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (void*) ; 
 void* blk_mq_init_queue (void*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (void*) ; 
 int nvme_enable_ctrl (struct nvme_ctrl*) ; 
 int nvme_init_identify (struct nvme_ctrl*) ; 
 int nvme_tcp_alloc_admin_queue (struct nvme_ctrl*) ; 
 void* nvme_tcp_alloc_tagset (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_tcp_free_admin_queue (struct nvme_ctrl*) ; 
 int nvme_tcp_start_queue (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_stop_queue (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_tcp_configure_admin_queue(struct nvme_ctrl *ctrl, bool new)
{
	int error;

	error = nvme_tcp_alloc_admin_queue(ctrl);
	if (error)
		return error;

	if (new) {
		ctrl->admin_tagset = nvme_tcp_alloc_tagset(ctrl, true);
		if (IS_ERR(ctrl->admin_tagset)) {
			error = PTR_ERR(ctrl->admin_tagset);
			goto out_free_queue;
		}

		ctrl->fabrics_q = blk_mq_init_queue(ctrl->admin_tagset);
		if (IS_ERR(ctrl->fabrics_q)) {
			error = PTR_ERR(ctrl->fabrics_q);
			goto out_free_tagset;
		}

		ctrl->admin_q = blk_mq_init_queue(ctrl->admin_tagset);
		if (IS_ERR(ctrl->admin_q)) {
			error = PTR_ERR(ctrl->admin_q);
			goto out_cleanup_fabrics_q;
		}
	}

	error = nvme_tcp_start_queue(ctrl, 0);
	if (error)
		goto out_cleanup_queue;

	error = nvme_enable_ctrl(ctrl);
	if (error)
		goto out_stop_queue;

	blk_mq_unquiesce_queue(ctrl->admin_q);

	error = nvme_init_identify(ctrl);
	if (error)
		goto out_stop_queue;

	return 0;

out_stop_queue:
	nvme_tcp_stop_queue(ctrl, 0);
out_cleanup_queue:
	if (new)
		blk_cleanup_queue(ctrl->admin_q);
out_cleanup_fabrics_q:
	if (new)
		blk_cleanup_queue(ctrl->fabrics_q);
out_free_tagset:
	if (new)
		blk_mq_free_tag_set(ctrl->admin_tagset);
out_free_queue:
	nvme_tcp_free_admin_queue(ctrl);
	return error;
}