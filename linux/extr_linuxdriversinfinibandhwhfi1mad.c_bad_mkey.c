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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dr_rtn_path; int /*<<< orphan*/  dr_trunc_hop; int /*<<< orphan*/  dr_slid; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; int /*<<< orphan*/  lid; } ;
struct TYPE_5__ {TYPE_1__ ntc_256; int /*<<< orphan*/  issuer_lid; } ;
struct trap_node {int len; TYPE_2__ data; } ;
struct ib_mad_hdr {scalar_t__ mgmt_class; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; } ;
struct hfi1_ibport {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_DR_NOTICE ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_DR_TRUNC ; 
 int /*<<< orphan*/  IB_NOTICE_TYPE_SECURITY ; 
 int /*<<< orphan*/  OPA_TRAP_BAD_M_KEY ; 
 struct trap_node* create_trap_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  send_trap (struct hfi1_ibport*,struct trap_node*) ; 

__attribute__((used)) static void bad_mkey(struct hfi1_ibport *ibp, struct ib_mad_hdr *mad,
		     __be64 mkey, __be32 dr_slid, u8 return_path[], u8 hop_cnt)
{
	struct trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_SECURITY, OPA_TRAP_BAD_M_KEY,
				lid);
	if (!trap)
		return;

	/* Send violation trap */
	trap->data.ntc_256.lid = trap->data.issuer_lid;
	trap->data.ntc_256.method = mad->method;
	trap->data.ntc_256.attr_id = mad->attr_id;
	trap->data.ntc_256.attr_mod = mad->attr_mod;
	trap->data.ntc_256.mkey = mkey;
	if (mad->mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
		trap->data.ntc_256.dr_slid = dr_slid;
		trap->data.ntc_256.dr_trunc_hop = IB_NOTICE_TRAP_DR_NOTICE;
		if (hop_cnt > ARRAY_SIZE(trap->data.ntc_256.dr_rtn_path)) {
			trap->data.ntc_256.dr_trunc_hop |=
				IB_NOTICE_TRAP_DR_TRUNC;
			hop_cnt = ARRAY_SIZE(trap->data.ntc_256.dr_rtn_path);
		}
		trap->data.ntc_256.dr_trunc_hop |= hop_cnt;
		memcpy(trap->data.ntc_256.dr_rtn_path, return_path,
		       hop_cnt);
	}

	trap->len = sizeof(trap->data);

	send_trap(ibp, trap);
}