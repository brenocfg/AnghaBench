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
struct nvme_ctrl {TYPE_1__* ops; int /*<<< orphan*/  subsystem; } ;
struct TYPE_2__ {int (* reg_write32 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  NVME_REG_NSSR ; 
 int stub1 (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int nvme_reset_subsystem(struct nvme_ctrl *ctrl)
{
	if (!ctrl->subsystem)
		return -ENOTTY;
	return ctrl->ops->reg_write32(ctrl, NVME_REG_NSSR, 0x4E564D65);
}