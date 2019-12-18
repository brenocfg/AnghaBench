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
struct nvme_fc_ctrl {struct nvme_ctrl ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nvme_fc_ctrl_put (struct nvme_fc_ctrl*) ; 
 struct nvme_fc_ctrl* to_fc_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void
nvme_fc_nvme_ctrl_freed(struct nvme_ctrl *nctrl)
{
	struct nvme_fc_ctrl *ctrl = to_fc_ctrl(nctrl);

	WARN_ON(nctrl != &ctrl->ctrl);

	nvme_fc_ctrl_put(ctrl);
}