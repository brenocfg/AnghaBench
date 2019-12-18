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
struct bfad_s {int dummy; } ;
struct bfa_s {int /*<<< orphan*/  fcs; } ;
struct bfa_fcs_fabric_s {struct bfa_fcs_s* fcs; int /*<<< orphan*/  bport; int /*<<< orphan*/  wc; int /*<<< orphan*/  lps; int /*<<< orphan*/  vf_q; int /*<<< orphan*/  vport_q; } ;
struct bfa_fcs_s {struct bfa_s* bfa; scalar_t__ num_rport_logins; int /*<<< orphan*/  min_cfg; struct bfad_s* bfad; struct bfa_fcs_fabric_s fabric; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_VF_ID_NULL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcport_event_register (struct bfa_s*,int /*<<< orphan*/ ,struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_delete_comp ; 
 int /*<<< orphan*/  bfa_fcs_fabric_sm_uninit ; 
 int /*<<< orphan*/  bfa_fcs_lport_attach (int /*<<< orphan*/ *,struct bfa_fcs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_port_event_handler ; 
 int /*<<< orphan*/  bfa_fcs_uf_recv ; 
 int /*<<< orphan*/  bfa_lps_alloc (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_uf_recv_register (struct bfa_s*,int /*<<< orphan*/ ,struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_wc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_fabric_s*) ; 
 int /*<<< orphan*/  bfa_wc_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcbuild_init () ; 
 int /*<<< orphan*/  memset (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ,int) ; 

void
bfa_fcs_attach(struct bfa_fcs_s *fcs, struct bfa_s *bfa, struct bfad_s *bfad,
	       bfa_boolean_t min_cfg)
{
	struct bfa_fcs_fabric_s *fabric = &fcs->fabric;

	fcs->bfa = bfa;
	fcs->bfad = bfad;
	fcs->min_cfg = min_cfg;
	fcs->num_rport_logins = 0;

	bfa->fcs = BFA_TRUE;
	fcbuild_init();

	bfa_fcport_event_register(fcs->bfa, bfa_fcs_port_event_handler, fcs);
	bfa_uf_recv_register(fcs->bfa, bfa_fcs_uf_recv, fcs);

	memset(fabric, 0, sizeof(struct bfa_fcs_fabric_s));

	/*
	 * Initialize base fabric.
	 */
	fabric->fcs = fcs;
	INIT_LIST_HEAD(&fabric->vport_q);
	INIT_LIST_HEAD(&fabric->vf_q);
	fabric->lps = bfa_lps_alloc(fcs->bfa);
	WARN_ON(!fabric->lps);

	/*
	 * Initialize fabric delete completion handler. Fabric deletion is
	 * complete when the last vport delete is complete.
	 */
	bfa_wc_init(&fabric->wc, bfa_fcs_fabric_delete_comp, fabric);
	bfa_wc_up(&fabric->wc); /* For the base port */

	bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_uninit);
	bfa_fcs_lport_attach(&fabric->bport, fabric->fcs, FC_VF_ID_NULL, NULL);
}