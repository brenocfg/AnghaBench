#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvmet_req {TYPE_4__* sq; TYPE_2__* cmd; } ;
struct TYPE_8__ {TYPE_3__* ctrl; } ;
struct TYPE_7__ {int /*<<< orphan*/  aen_masked; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdw10; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvmet_clear_aen_bit(struct nvmet_req *req, u32 bn)
{
	int rae = le32_to_cpu(req->cmd->common.cdw10) & 1 << 15;

	if (!rae)
		clear_bit(bn, &req->sq->ctrl->aen_masked);
}