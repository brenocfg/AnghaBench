#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* attr; } ;
struct bfa_s {TYPE_2__ ioc; } ;
struct bfa_port_cfg_s {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  q_depth; int /*<<< orphan*/  path_tov; int /*<<< orphan*/  trunked; int /*<<< orphan*/  topology; int /*<<< orphan*/  speed; } ;
struct bfa_port_attr_s {int /*<<< orphan*/  fcoe_vlan; int /*<<< orphan*/  port_state; int /*<<< orphan*/  fec_state; TYPE_4__ pport_cfg; int /*<<< orphan*/  link_e2e_beacon; int /*<<< orphan*/  beacon; int /*<<< orphan*/  topology; int /*<<< orphan*/  cos_supported; int /*<<< orphan*/  speed; int /*<<< orphan*/  speed_supported; int /*<<< orphan*/  factorynwwn; int /*<<< orphan*/  factorypwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;
struct TYPE_10__ {int /*<<< orphan*/  trunked; int /*<<< orphan*/  topology; int /*<<< orphan*/  speed; } ;
struct bfa_fcport_s {int /*<<< orphan*/  fcoe_vlan; TYPE_3__* bfa; int /*<<< orphan*/  fec_state; int /*<<< orphan*/  sm; int /*<<< orphan*/  link_e2e_beacon; int /*<<< orphan*/  beacon; TYPE_5__ cfg; int /*<<< orphan*/  topology; int /*<<< orphan*/  speed; int /*<<< orphan*/  speed_sup; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;
struct TYPE_8__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_6__ {int /*<<< orphan*/  mfg_nwwn; int /*<<< orphan*/  mfg_pwwn; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_PORT_ST_FWMISMATCH ; 
 int /*<<< orphan*/  BFA_PORT_ST_IOCDIS ; 
 int /*<<< orphan*/  BFA_PORT_ST_PREBOOT_DISABLED ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  bfa_fcpim_path_tov_get (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcpim_qdepth_get (struct bfa_s*) ; 
 scalar_t__ bfa_fcport_is_pbcdisabled (struct bfa_s*) ; 
 scalar_t__ bfa_ioc_fw_mismatch (int /*<<< orphan*/ *) ; 
 scalar_t__ bfa_ioc_is_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal_port_sm_table ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (struct bfa_port_attr_s*,int /*<<< orphan*/ ,int) ; 

void
bfa_fcport_get_attr(struct bfa_s *bfa, struct bfa_port_attr_s *attr)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	memset(attr, 0, sizeof(struct bfa_port_attr_s));

	attr->nwwn = fcport->nwwn;
	attr->pwwn = fcport->pwwn;

	attr->factorypwwn =  bfa->ioc.attr->mfg_pwwn;
	attr->factorynwwn =  bfa->ioc.attr->mfg_nwwn;

	memcpy(&attr->pport_cfg, &fcport->cfg,
		sizeof(struct bfa_port_cfg_s));
	/* speed attributes */
	attr->pport_cfg.speed = fcport->cfg.speed;
	attr->speed_supported = fcport->speed_sup;
	attr->speed = fcport->speed;
	attr->cos_supported = FC_CLASS_3;

	/* topology attributes */
	attr->pport_cfg.topology = fcport->cfg.topology;
	attr->topology = fcport->topology;
	attr->pport_cfg.trunked = fcport->cfg.trunked;

	/* beacon attributes */
	attr->beacon = fcport->beacon;
	attr->link_e2e_beacon = fcport->link_e2e_beacon;

	attr->pport_cfg.path_tov  = bfa_fcpim_path_tov_get(bfa);
	attr->pport_cfg.q_depth  = bfa_fcpim_qdepth_get(bfa);
	attr->port_state = bfa_sm_to_state(hal_port_sm_table, fcport->sm);

	attr->fec_state = fcport->fec_state;

	/* PBC Disabled State */
	if (bfa_fcport_is_pbcdisabled(bfa))
		attr->port_state = BFA_PORT_ST_PREBOOT_DISABLED;
	else {
		if (bfa_ioc_is_disabled(&fcport->bfa->ioc))
			attr->port_state = BFA_PORT_ST_IOCDIS;
		else if (bfa_ioc_fw_mismatch(&fcport->bfa->ioc))
			attr->port_state = BFA_PORT_ST_FWMISMATCH;
	}

	/* FCoE vlan */
	attr->fcoe_vlan = fcport->fcoe_vlan;
}