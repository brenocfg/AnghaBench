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
struct amdgpu_device {int dummy; } ;
typedef  enum idh_request { ____Placeholder_idh_request } idh_request ;

/* Variables and functions */
 int /*<<< orphan*/  IDH_READY_TO_ACCESS_GPU ; 
 int IDH_REQ_GPU_FINI_ACCESS ; 
 int IDH_REQ_GPU_INIT_ACCESS ; 
 int IDH_REQ_GPU_RESET_ACCESS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  xgpu_vi_mailbox_set_valid (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  xgpu_vi_mailbox_trans_msg (struct amdgpu_device*,int) ; 
 int xgpu_vi_poll_ack (struct amdgpu_device*) ; 
 int xgpu_vi_poll_msg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_vi_send_access_requests(struct amdgpu_device *adev,
					enum idh_request request)
{
	int r;

	xgpu_vi_mailbox_trans_msg(adev, request);

	/* start to poll ack */
	r = xgpu_vi_poll_ack(adev);
	if (r)
		return r;

	xgpu_vi_mailbox_set_valid(adev, false);

	/* start to check msg if request is idh_req_gpu_init_access */
	if (request == IDH_REQ_GPU_INIT_ACCESS ||
		request == IDH_REQ_GPU_FINI_ACCESS ||
		request == IDH_REQ_GPU_RESET_ACCESS) {
		r = xgpu_vi_poll_msg(adev, IDH_READY_TO_ACCESS_GPU);
		if (r) {
			pr_err("Doesn't get ack from pf, give up\n");
			return r;
		}
	}

	return 0;
}