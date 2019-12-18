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
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_AQ_DEPTH ; 
 int nvme_tcp_alloc_async_req (int /*<<< orphan*/ ) ; 
 int nvme_tcp_alloc_queue (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_free_queue (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static int nvme_tcp_alloc_admin_queue(struct nvme_ctrl *ctrl)
{
	int ret;

	ret = nvme_tcp_alloc_queue(ctrl, 0, NVME_AQ_DEPTH);
	if (ret)
		return ret;

	ret = nvme_tcp_alloc_async_req(to_tcp_ctrl(ctrl));
	if (ret)
		goto out_free_queue;

	return 0;

out_free_queue:
	nvme_tcp_free_queue(ctrl, 0);
	return ret;
}