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
struct nvmet_req {TYPE_2__* sq; } ;
struct TYPE_4__ {TYPE_1__* ctrl; } ;
struct TYPE_3__ {int kato; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int) ; 

void nvmet_get_feat_kato(struct nvmet_req *req)
{
	nvmet_set_result(req, req->sq->ctrl->kato * 1000);
}