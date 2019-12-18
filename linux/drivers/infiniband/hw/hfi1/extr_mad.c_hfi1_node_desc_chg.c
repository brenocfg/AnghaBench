#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  change_flags; int /*<<< orphan*/  lid; } ;
struct TYPE_5__ {TYPE_1__ ntc_144; int /*<<< orphan*/  issuer_lid; } ;
struct trap_node {int len; TYPE_2__ data; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NOTICE_TYPE_INFO ; 
 int /*<<< orphan*/  OPA_NOTICE_TRAP_NODE_DESC_CHG ; 
 int /*<<< orphan*/  OPA_TRAP_CHANGE_CAPABILITY ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct trap_node* create_trap_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  send_trap (struct hfi1_ibport*,struct trap_node*) ; 

void hfi1_node_desc_chg(struct hfi1_ibport *ibp)
{
	struct trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_INFO,
				OPA_TRAP_CHANGE_CAPABILITY,
				lid);
	if (!trap)
		return;

	trap->data.ntc_144.lid = trap->data.issuer_lid;
	trap->data.ntc_144.change_flags =
		cpu_to_be16(OPA_NOTICE_TRAP_NODE_DESC_CHG);

	trap->len = sizeof(trap->data);
	send_trap(ibp, trap);
}