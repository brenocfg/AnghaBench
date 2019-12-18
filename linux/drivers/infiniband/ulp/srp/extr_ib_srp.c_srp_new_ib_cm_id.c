#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  service_id; int /*<<< orphan*/  pkey; int /*<<< orphan*/  orig_dgid; } ;
struct srp_target_port {TYPE_5__ ib_cm; int /*<<< orphan*/  sgid; TYPE_2__* srp_host; } ;
struct TYPE_8__ {int /*<<< orphan*/  service_id; int /*<<< orphan*/  pkey; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  rec_type; } ;
struct TYPE_9__ {TYPE_3__ path; struct ib_cm_id* cm_id; } ;
struct srp_rdma_ch {TYPE_4__ ib_cm; struct srp_target_port* target; } ;
struct ib_cm_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; TYPE_1__* srp_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_cm_id*) ; 
 int PTR_ERR (struct ib_cm_id*) ; 
 int /*<<< orphan*/  SA_PATH_REC_TYPE_IB ; 
 int /*<<< orphan*/  SA_PATH_REC_TYPE_OPA ; 
 struct ib_cm_id* ib_create_cm_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct srp_rdma_ch*) ; 
 int /*<<< orphan*/  ib_destroy_cm_id (struct ib_cm_id*) ; 
 scalar_t__ rdma_cap_opa_ah (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_ib_cm_handler ; 

__attribute__((used)) static int srp_new_ib_cm_id(struct srp_rdma_ch *ch)
{
	struct srp_target_port *target = ch->target;
	struct ib_cm_id *new_cm_id;

	new_cm_id = ib_create_cm_id(target->srp_host->srp_dev->dev,
				    srp_ib_cm_handler, ch);
	if (IS_ERR(new_cm_id))
		return PTR_ERR(new_cm_id);

	if (ch->ib_cm.cm_id)
		ib_destroy_cm_id(ch->ib_cm.cm_id);
	ch->ib_cm.cm_id = new_cm_id;
	if (rdma_cap_opa_ah(target->srp_host->srp_dev->dev,
			    target->srp_host->port))
		ch->ib_cm.path.rec_type = SA_PATH_REC_TYPE_OPA;
	else
		ch->ib_cm.path.rec_type = SA_PATH_REC_TYPE_IB;
	ch->ib_cm.path.sgid = target->sgid;
	ch->ib_cm.path.dgid = target->ib_cm.orig_dgid;
	ch->ib_cm.path.pkey = target->ib_cm.pkey;
	ch->ib_cm.path.service_id = target->ib_cm.service_id;

	return 0;
}