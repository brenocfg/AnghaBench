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
struct request {int dummy; } ;
struct nvme_ctrl {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_LIVE ; 
 int __nvmf_check_ready (struct nvme_ctrl*,struct request*,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline bool nvmf_check_ready(struct nvme_ctrl *ctrl, struct request *rq,
		bool queue_live)
{
	if (likely(ctrl->state == NVME_CTRL_LIVE))
		return true;
	return __nvmf_check_ready(ctrl, rq, queue_live);
}