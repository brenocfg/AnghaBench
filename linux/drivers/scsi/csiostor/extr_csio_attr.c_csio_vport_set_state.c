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
struct csio_lnode {int flags; struct csio_lnode* pln; struct fc_vport* fc_vport; } ;

/* Variables and functions */
 int CSIO_LNF_NPIVSUPP ; 
 int /*<<< orphan*/  FC_VPORT_ACTIVE ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int /*<<< orphan*/  FC_VPORT_NO_FABRIC_SUPP ; 
 int /*<<< orphan*/  csio_lnode_state_to_str (struct csio_lnode*,char*) ; 
 int /*<<< orphan*/  fc_vport_set_state (struct fc_vport*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
csio_vport_set_state(struct csio_lnode *ln)
{
	struct fc_vport *fc_vport = ln->fc_vport;
	struct csio_lnode  *pln = ln->pln;
	char state[16];

	/* Set fc vport state based on phyiscal lnode */
	csio_lnode_state_to_str(pln, state);
	if (strcmp(state, "READY")) {
		fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
		return;
	}

	if (!(pln->flags & CSIO_LNF_NPIVSUPP)) {
		fc_vport_set_state(fc_vport, FC_VPORT_NO_FABRIC_SUPP);
		return;
	}

	/* Set fc vport state based on virtual lnode */
	csio_lnode_state_to_str(ln, state);
	if (strcmp(state, "READY")) {
		fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
		return;
	}
	fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
}