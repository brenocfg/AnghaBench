#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fc_vport {int dummy; } ;
struct fc_lport {scalar_t__ state; scalar_t__ npiv_enabled; struct fc_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_INITIALIZING ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int /*<<< orphan*/  FC_VPORT_NO_FABRIC_SUPP ; 
 scalar_t__ LPORT_ST_DISABLED ; 
 scalar_t__ LPORT_ST_READY ; 
 int /*<<< orphan*/  __fc_linkdown (struct fc_lport*) ; 
 int /*<<< orphan*/  __fc_linkup (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_vport_set_state (struct fc_vport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fc_vport_setlink(struct fc_lport *n_port,
			       struct fc_lport *vn_port)
{
	struct fc_vport *vport = vn_port->vport;

	if (vn_port->state == LPORT_ST_DISABLED)
		return;

	if (n_port->state == LPORT_ST_READY) {
		if (n_port->npiv_enabled) {
			fc_vport_set_state(vport, FC_VPORT_INITIALIZING);
			__fc_linkup(vn_port);
		} else {
			fc_vport_set_state(vport, FC_VPORT_NO_FABRIC_SUPP);
			__fc_linkdown(vn_port);
		}
	} else {
		fc_vport_set_state(vport, FC_VPORT_LINKDOWN);
		__fc_linkdown(vn_port);
	}
}