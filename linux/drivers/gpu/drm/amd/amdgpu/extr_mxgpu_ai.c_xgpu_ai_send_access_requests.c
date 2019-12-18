#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  checksum_key; } ;
struct TYPE_4__ {TYPE_1__ fw_reserve; } ;
struct amdgpu_device {TYPE_2__ virt; } ;
typedef  enum idh_request { ____Placeholder_idh_request } idh_request ;

/* Variables and functions */
 int /*<<< orphan*/  IDH_READY_TO_ACCESS_GPU ; 
 int IDH_REQ_GPU_FINI_ACCESS ; 
 int IDH_REQ_GPU_INIT_ACCESS ; 
 int IDH_REQ_GPU_RESET_ACCESS ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW2 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_trans_msg (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xgpu_ai_poll_msg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_ai_send_access_requests(struct amdgpu_device *adev,
					enum idh_request req)
{
	int r;

	xgpu_ai_mailbox_trans_msg(adev, req, 0, 0, 0);

	/* start to check msg if request is idh_req_gpu_init_access */
	if (req == IDH_REQ_GPU_INIT_ACCESS ||
		req == IDH_REQ_GPU_FINI_ACCESS ||
		req == IDH_REQ_GPU_RESET_ACCESS) {
		r = xgpu_ai_poll_msg(adev, IDH_READY_TO_ACCESS_GPU);
		if (r) {
			pr_err("Doesn't get READY_TO_ACCESS_GPU from pf, give up\n");
			return r;
		}
		/* Retrieve checksum from mailbox2 */
		if (req == IDH_REQ_GPU_INIT_ACCESS || req == IDH_REQ_GPU_RESET_ACCESS) {
			adev->virt.fw_reserve.checksum_key =
				RREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0,
					mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW2));
		}
	}

	return 0;
}