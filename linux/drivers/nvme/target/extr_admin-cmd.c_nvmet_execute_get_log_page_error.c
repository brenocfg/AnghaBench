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
typedef  size_t u64 ;
struct nvmet_req {TYPE_1__* sq; } ;
struct nvmet_ctrl {size_t err_counter; int /*<<< orphan*/  error_lock; int /*<<< orphan*/ * slots; } ;
struct nvme_error_slot {int dummy; } ;
typedef  int off_t ;
struct TYPE_2__ {struct nvmet_ctrl* ctrl; } ;

/* Variables and functions */
 size_t NVMET_ERROR_LOG_SLOTS ; 
 scalar_t__ nvmet_copy_to_sgl (struct nvmet_req*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvmet_execute_get_log_page_error(struct nvmet_req *req)
{
	struct nvmet_ctrl *ctrl = req->sq->ctrl;
	unsigned long flags;
	off_t offset = 0;
	u64 slot;
	u64 i;

	spin_lock_irqsave(&ctrl->error_lock, flags);
	slot = ctrl->err_counter % NVMET_ERROR_LOG_SLOTS;

	for (i = 0; i < NVMET_ERROR_LOG_SLOTS; i++) {
		if (nvmet_copy_to_sgl(req, offset, &ctrl->slots[slot],
				sizeof(struct nvme_error_slot)))
			break;

		if (slot == 0)
			slot = NVMET_ERROR_LOG_SLOTS - 1;
		else
			slot--;
		offset += sizeof(struct nvme_error_slot);
	}
	spin_unlock_irqrestore(&ctrl->error_lock, flags);
	nvmet_req_complete(req, 0);
}