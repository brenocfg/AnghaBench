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
typedef  scalar_t__ u32 ;
struct nvme_fc_rport {struct nvme_fc_lport* lport; } ;
struct TYPE_4__ {scalar_t__ port_state; } ;
struct nvme_fc_lport {TYPE_2__ localport; TYPE_1__* ops; int /*<<< orphan*/  act_rport_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* localport_delete ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ FC_OBJSTATE_DELETED ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
nvme_fc_rport_inactive_on_lport(struct nvme_fc_rport *rport)
{
	struct nvme_fc_lport *lport = rport->lport;
	u32 cnt;

	cnt = atomic_dec_return(&lport->act_rport_cnt);
	if (cnt == 0 && lport->localport.port_state == FC_OBJSTATE_DELETED)
		lport->ops->localport_delete(&lport->localport);
}