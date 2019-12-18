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
typedef  void* wwn_t ;
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_6__ {int npiv_supp; void* bbcred; void* security; void* ciro; void* rxsz; } ;
struct TYPE_5__ {void* rxsz; } ;
struct TYPE_4__ {int /*<<< orphan*/  els_code; } ;
struct fc_logi_s {TYPE_3__ csp; int /*<<< orphan*/ * vvl; void* node_name; void* port_name; TYPE_2__ class3; TYPE_1__ els_cmd; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_FLOGI ; 
 int /*<<< orphan*/  FC_FABRIC_PORT ; 
 int /*<<< orphan*/  FLOGI_VVL_BRCD ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct fc_logi_s*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  plogi_tmpl ; 

u16
fc_flogi_build(struct fchs_s *fchs, struct fc_logi_s *flogi, u32 s_id,
		u16 ox_id, wwn_t port_name, wwn_t node_name, u16 pdu_size,
	       u8 set_npiv, u8 set_auth, u16 local_bb_credits)
{
	u32        d_id = bfa_hton3b(FC_FABRIC_PORT);
	__be32	*vvl_info;

	memcpy(flogi, &plogi_tmpl, sizeof(struct fc_logi_s));

	flogi->els_cmd.els_code = FC_ELS_FLOGI;
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	flogi->csp.rxsz = flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	/*
	 * Set the NPIV Capability Bit ( word 1, bit 31) of Common
	 * Service Parameters.
	 */
	flogi->csp.ciro = set_npiv;

	/* set AUTH capability */
	flogi->csp.security = set_auth;

	flogi->csp.bbcred = cpu_to_be16(local_bb_credits);

	/* Set brcd token in VVL */
	vvl_info = (u32 *)&flogi->vvl[0];

	/* set the flag to indicate the presence of VVL */
	flogi->csp.npiv_supp    = 1; /* @todo. field name is not correct */
	vvl_info[0]	= cpu_to_be32(FLOGI_VVL_BRCD);

	return sizeof(struct fc_logi_s);
}