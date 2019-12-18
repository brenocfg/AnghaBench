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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_4__* sq; TYPE_2__* cmd; } ;
struct TYPE_8__ {TYPE_3__* ctrl; } ;
struct TYPE_7__ {int /*<<< orphan*/  kato; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdw11; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int /*<<< orphan*/ ) ; 

u16 nvmet_set_feat_kato(struct nvmet_req *req)
{
	u32 val32 = le32_to_cpu(req->cmd->common.cdw11);

	req->sq->ctrl->kato = DIV_ROUND_UP(val32, 1000);

	nvmet_set_result(req, req->sq->ctrl->kato);

	return 0;
}