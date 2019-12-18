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
struct bfa_lport_attr_s {int /*<<< orphan*/  state; int /*<<< orphan*/  port_type; int /*<<< orphan*/  fpma_mac; int /*<<< orphan*/  fabric_ip_addr; int /*<<< orphan*/  fabric_name; void* authfail; void* loopback; int /*<<< orphan*/  port_cfg; scalar_t__ pid; } ;
struct bfa_fcs_lport_s {TYPE_3__* lps; struct bfa_fcs_lport_s* fabric; TYPE_2__* vport; int /*<<< orphan*/  oper_type; int /*<<< orphan*/  port_cfg; scalar_t__ pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  lp_mac; } ;
struct TYPE_5__ {TYPE_1__* lps; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_IPADDR_SZ ; 
 int /*<<< orphan*/  BFA_LPORT_UNINIT ; 
 int /*<<< orphan*/  BFA_PORT_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  BFA_PORT_TYPE_VPORT ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_auth_failed ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_loopback ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fabric_ipaddr (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fabric_name (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_sm_online ; 
 void* bfa_sm_cmp_state (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_lport_get_attr(
	struct bfa_fcs_lport_s *port,
	struct bfa_lport_attr_s *port_attr)
{
	if (bfa_sm_cmp_state(port, bfa_fcs_lport_sm_online))
		port_attr->pid = port->pid;
	else
		port_attr->pid = 0;

	port_attr->port_cfg = port->port_cfg;

	if (port->fabric) {
		port_attr->port_type = port->fabric->oper_type;
		port_attr->loopback = bfa_sm_cmp_state(port->fabric,
				bfa_fcs_fabric_sm_loopback);
		port_attr->authfail =
			bfa_sm_cmp_state(port->fabric,
				bfa_fcs_fabric_sm_auth_failed);
		port_attr->fabric_name  = bfa_fcs_lport_get_fabric_name(port);
		memcpy(port_attr->fabric_ip_addr,
			bfa_fcs_lport_get_fabric_ipaddr(port),
			BFA_FCS_FABRIC_IPADDR_SZ);

		if (port->vport != NULL) {
			port_attr->port_type = BFA_PORT_TYPE_VPORT;
			port_attr->fpma_mac =
				port->vport->lps->lp_mac;
		} else {
			port_attr->fpma_mac =
				port->fabric->lps->lp_mac;
		}
	} else {
		port_attr->port_type = BFA_PORT_TYPE_UNKNOWN;
		port_attr->state = BFA_LPORT_UNINIT;
	}
}