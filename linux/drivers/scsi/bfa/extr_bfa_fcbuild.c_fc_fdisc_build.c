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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxsz; } ;
struct TYPE_6__ {int /*<<< orphan*/  rxsz; } ;
struct TYPE_5__ {int /*<<< orphan*/  els_code; } ;
struct fc_logi_s {void* node_name; void* port_name; TYPE_1__ class3; TYPE_3__ csp; TYPE_2__ els_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_FDISC ; 
 int /*<<< orphan*/  FC_FABRIC_PORT ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct fc_logi_s*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  plogi_tmpl ; 

u16
fc_fdisc_build(struct fchs_s *fchs, struct fc_logi_s *flogi, u32 s_id,
		u16 ox_id, wwn_t port_name, wwn_t node_name, u16 pdu_size)
{
	u32        d_id = bfa_hton3b(FC_FABRIC_PORT);

	memcpy(flogi, &plogi_tmpl, sizeof(struct fc_logi_s));

	flogi->els_cmd.els_code = FC_ELS_FDISC;
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	flogi->csp.rxsz = flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	return sizeof(struct fc_logi_s);
}