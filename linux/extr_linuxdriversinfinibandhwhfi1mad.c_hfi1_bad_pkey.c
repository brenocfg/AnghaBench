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
typedef  int u32 ;
struct TYPE_6__ {int sl; void* qp2; void* qp1; void* key; void* lid2; void* lid1; } ;
struct TYPE_7__ {TYPE_2__ ntc_257_258; } ;
struct trap_node {int len; TYPE_3__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_violations; int /*<<< orphan*/  n_pkt_drops; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;
struct TYPE_8__ {int lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NOTICE_TYPE_SECURITY ; 
 int /*<<< orphan*/  OPA_TRAP_BAD_P_KEY ; 
 void* cpu_to_be32 (int) ; 
 struct trap_node* create_trap_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  send_trap (struct hfi1_ibport*,struct trap_node*) ; 

void hfi1_bad_pkey(struct hfi1_ibport *ibp, u32 key, u32 sl,
		   u32 qp1, u32 qp2, u32 lid1, u32 lid2)
{
	struct trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	ibp->rvp.n_pkt_drops++;
	ibp->rvp.pkey_violations++;

	trap = create_trap_node(IB_NOTICE_TYPE_SECURITY, OPA_TRAP_BAD_P_KEY,
				lid);
	if (!trap)
		return;

	/* Send violation trap */
	trap->data.ntc_257_258.lid1 = cpu_to_be32(lid1);
	trap->data.ntc_257_258.lid2 = cpu_to_be32(lid2);
	trap->data.ntc_257_258.key = cpu_to_be32(key);
	trap->data.ntc_257_258.sl = sl << 3;
	trap->data.ntc_257_258.qp1 = cpu_to_be32(qp1);
	trap->data.ntc_257_258.qp2 = cpu_to_be32(qp2);

	trap->len = sizeof(trap->data);
	send_trap(ibp, trap);
}