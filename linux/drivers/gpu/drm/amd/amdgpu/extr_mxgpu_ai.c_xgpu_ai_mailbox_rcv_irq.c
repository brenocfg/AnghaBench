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
struct amdgpu_iv_entry {int dummy; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flr_work; } ;
struct amdgpu_device {TYPE_1__ virt; } ;
typedef  enum idh_event { ____Placeholder_idh_event } idh_event ;

/* Variables and functions */
#define  IDH_CLR_MSG_BUF 132 
#define  IDH_FLR_NOTIFICATION 131 
#define  IDH_FLR_NOTIFICATION_CMPL 130 
#define  IDH_QUERY_ALIVE 129 
#define  IDH_READY_TO_ACCESS_GPU 128 
 int /*<<< orphan*/  amdgpu_sriov_runtime (struct amdgpu_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int xgpu_ai_mailbox_peek_msg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_send_ack (struct amdgpu_device*) ; 

__attribute__((used)) static int xgpu_ai_mailbox_rcv_irq(struct amdgpu_device *adev,
				   struct amdgpu_irq_src *source,
				   struct amdgpu_iv_entry *entry)
{
	enum idh_event event = xgpu_ai_mailbox_peek_msg(adev);

	switch (event) {
		case IDH_FLR_NOTIFICATION:
		if (amdgpu_sriov_runtime(adev))
			schedule_work(&adev->virt.flr_work);
		break;
		case IDH_QUERY_ALIVE:
			xgpu_ai_mailbox_send_ack(adev);
			break;
		/* READY_TO_ACCESS_GPU is fetched by kernel polling, IRQ can ignore
		 * it byfar since that polling thread will handle it,
		 * other msg like flr complete is not handled here.
		 */
		case IDH_CLR_MSG_BUF:
		case IDH_FLR_NOTIFICATION_CMPL:
		case IDH_READY_TO_ACCESS_GPU:
		default:
		break;
	}

	return 0;
}