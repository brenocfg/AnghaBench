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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
struct s_smc {TYPE_2__ mib; TYPE_1__* y; } ;
struct TYPE_6__ {scalar_t__ d_sba; scalar_t__ d_ess; scalar_t__ d_plc; scalar_t__ d_cfm; scalar_t__ d_pcm; scalar_t__ d_ecm; scalar_t__ d_rmt; scalar_t__ d_smtf; scalar_t__ d_smt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mib; } ;

/* Variables and functions */
 int NUMPHYS ; 
 int /*<<< orphan*/  PNMI_INIT (struct s_smc*) ; 
 int /*<<< orphan*/  cfm (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfm_init (struct s_smc*) ; 
 TYPE_3__ debug ; 
 int /*<<< orphan*/  ecm (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecm_init (struct s_smc*) ; 
 int /*<<< orphan*/  ev_init (struct s_smc*) ; 
 int /*<<< orphan*/  init_fddi_driver (struct s_smc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm (struct s_smc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_init (struct s_smc*) ; 
 int /*<<< orphan*/  rmt (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmt_init (struct s_smc*) ; 
 int /*<<< orphan*/  set_oem_spec_val (struct s_smc*) ; 
 int /*<<< orphan*/  smt_agent_init (struct s_smc*) ; 
 int /*<<< orphan*/  smt_agent_task (struct s_smc*) ; 
 int /*<<< orphan*/  smt_fixup_mib (struct s_smc*) ; 
 int /*<<< orphan*/  smt_init_evc (struct s_smc*) ; 
 int /*<<< orphan*/  smt_set_mac_opvalues (struct s_smc*) ; 
 int /*<<< orphan*/  smt_timer_init (struct s_smc*) ; 

int init_smt(struct s_smc *smc, u_char *mac_addr)
/* u_char *mac_addr;	canonical address or NULL */
{
	int	p ;

#if defined(DEBUG) && !defined(DEBUG_BRD)
	debug.d_smt = 0 ;
	debug.d_smtf = 0 ;
	debug.d_rmt = 0 ;
	debug.d_ecm = 0 ;
	debug.d_pcm = 0 ;
	debug.d_cfm = 0 ;

	debug.d_plc = 0 ;
#ifdef	ESS
	debug.d_ess = 0 ;
#endif
#ifdef	SBA
	debug.d_sba = 0 ;
#endif
#endif	/* DEBUG && !DEBUG_BRD */

	/* First initialize the ports mib->pointers */
	for ( p = 0; p < NUMPHYS; p ++ ) {
		smc->y[p].mib = & smc->mib.p[p] ;
	}

	set_oem_spec_val(smc) ;	
	(void) smt_set_mac_opvalues(smc) ;
	init_fddi_driver(smc,mac_addr) ;	/* HW driver */
	smt_fixup_mib(smc) ;		/* update values that depend on s.sas */

	ev_init(smc) ;			/* event queue */
#ifndef	SLIM_SMT
	smt_init_evc(smc) ;		/* evcs in MIB */
#endif	/* no SLIM_SMT */
	smt_timer_init(smc) ;		/* timer package */
	smt_agent_init(smc) ;		/* SMT frame manager */

	pcm_init(smc) ;			/* PCM state machine */
	ecm_init(smc) ;			/* ECM state machine */
	cfm_init(smc) ;			/* CFM state machine */
	rmt_init(smc) ;			/* RMT state machine */

	for (p = 0 ; p < NUMPHYS ; p++) {
		pcm(smc,p,0) ;		/* PCM A state machine */
	}
	ecm(smc,0) ;			/* ECM state machine */
	cfm(smc,0) ;			/* CFM state machine */
	rmt(smc,0) ;			/* RMT state machine */

	smt_agent_task(smc) ;		/* NIF FSM etc */

        PNMI_INIT(smc) ;                /* PNMI initialization */

	return 0;
}