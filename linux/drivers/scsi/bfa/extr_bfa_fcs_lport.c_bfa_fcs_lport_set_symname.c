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
struct TYPE_3__ {int /*<<< orphan*/  symname; } ;
struct TYPE_4__ {TYPE_1__ sym_name; } ;
struct bfa_fcs_lport_s {TYPE_2__ port_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_GET_NS_FROM_PORT (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_util_send_rspn_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_sm_online ; 
 scalar_t__ bfa_sm_cmp_state (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void
bfa_fcs_lport_set_symname(struct bfa_fcs_lport_s *port,
				char *symname)
{
	strcpy(port->port_cfg.sym_name.symname, symname);

	if (bfa_sm_cmp_state(port, bfa_fcs_lport_sm_online))
		bfa_fcs_lport_ns_util_send_rspn_id(
			BFA_FCS_GET_NS_FROM_PORT(port), NULL);
}