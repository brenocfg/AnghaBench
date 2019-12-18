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
struct TYPE_6__ {int sas; } ;
struct TYPE_10__ {int fddiSMTConnectionPolicy; } ;
struct s_smc {TYPE_3__* y; TYPE_1__ s; TYPE_5__ mib; } ;
struct s_phy {int np; int* t_val; int /*<<< orphan*/  pc_mode; int /*<<< orphan*/  wc_flag; void* cf_loop; int /*<<< orphan*/  phy_name; int /*<<< orphan*/  pc_lem_fail; struct fddi_mib_p* mib; } ;
struct TYPE_9__ {int T_val; } ;
struct fddi_mib_p {int fddiPORTMy_Type; int fddiPORTNeighborType; TYPE_4__ fddiPORTMacIndicated; int /*<<< orphan*/  fddiPORTPC_Withhold; int /*<<< orphan*/  fddiPORTConnectState; int /*<<< orphan*/  fddiPORTLCTFail_Ct; } ;
struct TYPE_8__ {TYPE_2__* mib; } ;
struct TYPE_7__ {int /*<<< orphan*/  fddiPORTConnectState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_PCMN (int,char*,int const,...) ; 
 int /*<<< orphan*/  EVENT_PCM ; 
 void* FALSE ; 
 int /*<<< orphan*/  INDEX_PORT ; 
 int PA ; 
 int PB ; 
 int /*<<< orphan*/  PCM_ACTIVE ; 
 int /*<<< orphan*/  PCM_CONNECTING ; 
 int /*<<< orphan*/  PCM_STANDBY ; 
 int /*<<< orphan*/  PC_START ; 
 int /*<<< orphan*/  PC_WH_NONE ; 
 int /*<<< orphan*/  PM_TREE ; 
 int POLICY_AA ; 
 int POLICY_AB ; 
 int POLICY_AM ; 
 int POLICY_AS ; 
 int POLICY_BA ; 
 int POLICY_BB ; 
 int POLICY_BM ; 
 int POLICY_BS ; 
 int POLICY_MA ; 
 int POLICY_MB ; 
 int POLICY_MM ; 
 int POLICY_MS ; 
 int POLICY_SA ; 
 int POLICY_SB ; 
 int POLICY_SM ; 
 int POLICY_SS ; 
 int PS ; 
#define  SMT_DAS 134 
 int /*<<< orphan*/  SMT_EVENT_PORT_CONNECTION ; 
#define  SMT_NAC 133 
#define  SMT_SAS 132 
#define  TA 131 
#define  TB 130 
#define  TM 129 
 void* TRUE ; 
#define  TS 128 
 int /*<<< orphan*/  lem_check_lct (struct s_smc*,struct s_phy*) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pc_tcode_actions(struct s_smc *smc, const int bit, struct s_phy *phy)
{
	int	np = phy->np ;
	struct fddi_mib_p	*mib ;

	mib = phy->mib ;

	switch(bit) {
	case 0:
		phy->t_val[0] = 0 ;		/* no escape used */
		break ;
	case 1:
		if (mib->fddiPORTMy_Type == TS || mib->fddiPORTMy_Type == TM)
			phy->t_val[1] = 1 ;
		else
			phy->t_val[1] = 0 ;
		break ;
	case 2 :
		if (mib->fddiPORTMy_Type == TB || mib->fddiPORTMy_Type == TM)
			phy->t_val[2] = 1 ;
		else
			phy->t_val[2] = 0 ;
		break ;
	case 3:
		{
		int	type,ne ;
		int	policy ;

		type = mib->fddiPORTMy_Type ;
		ne = mib->fddiPORTNeighborType ;
		policy = smc->mib.fddiSMTConnectionPolicy ;

		phy->t_val[3] = 1 ;	/* Accept connection */
		switch (type) {
		case TA :
			if (
				((policy & POLICY_AA) && ne == TA) ||
				((policy & POLICY_AB) && ne == TB) ||
				((policy & POLICY_AS) && ne == TS) ||
				((policy & POLICY_AM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			break ;
		case TB :
			if (
				((policy & POLICY_BA) && ne == TA) ||
				((policy & POLICY_BB) && ne == TB) ||
				((policy & POLICY_BS) && ne == TS) ||
				((policy & POLICY_BM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			break ;
		case TS :
			if (
				((policy & POLICY_SA) && ne == TA) ||
				((policy & POLICY_SB) && ne == TB) ||
				((policy & POLICY_SS) && ne == TS) ||
				((policy & POLICY_SM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			break ;
		case TM :
			if (	ne == TM ||
				((policy & POLICY_MA) && ne == TA) ||
				((policy & POLICY_MB) && ne == TB) ||
				((policy & POLICY_MS) && ne == TS) ||
				((policy & POLICY_MM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			break ;
		}
#ifndef	SLIM_SMT
		/*
		 * detect undesirable connection attempt event
		 */
		if (	(type == TA && ne == TA ) ||
			(type == TA && ne == TS ) ||
			(type == TB && ne == TB ) ||
			(type == TB && ne == TS ) ||
			(type == TS && ne == TA ) ||
			(type == TS && ne == TB ) ) {
			smt_srf_event(smc,SMT_EVENT_PORT_CONNECTION,
				(int) (INDEX_PORT+ phy->np) ,0) ;
		}
#endif
		}
		break ;
	case 4:
		if (mib->fddiPORTPC_Withhold == PC_WH_NONE) {
			if (phy->pc_lem_fail) {
				phy->t_val[4] = 1 ;	/* long */
				phy->t_val[5] = 0 ;
			}
			else {
				phy->t_val[4] = 0 ;
				if (mib->fddiPORTLCTFail_Ct > 0)
					phy->t_val[5] = 1 ;	/* medium */
				else
					phy->t_val[5] = 0 ;	/* short */

				/*
				 * Implementers choice: use medium
				 * instead of short when undesired
				 * connection attempt is made.
				 */
				if (phy->wc_flag)
					phy->t_val[5] = 1 ;	/* medium */
			}
			mib->fddiPORTConnectState = PCM_CONNECTING ;
		}
		else {
			mib->fddiPORTConnectState = PCM_STANDBY ;
			phy->t_val[4] = 1 ;	/* extended */
			phy->t_val[5] = 1 ;
		}
		break ;
	case 5:
		break ;
	case 6:
		/* we do NOT have a MAC for LCT */
		phy->t_val[6] = 0 ;
		break ;
	case 7:
		phy->cf_loop = FALSE ;
		lem_check_lct(smc,phy) ;
		if (phy->pc_lem_fail) {
			DB_PCMN(1, "PCM %c : E104 LCT failed", phy->phy_name);
			phy->t_val[7] = 1 ;
		}
		else
			phy->t_val[7] = 0 ;
		break ;
	case 8:
		phy->t_val[8] = 0 ;	/* Don't request MAC loopback */
		break ;
	case 9:
		phy->cf_loop = 0 ;
		if ((mib->fddiPORTPC_Withhold != PC_WH_NONE) ||
		     ((smc->s.sas == SMT_DAS) && (phy->wc_flag))) {
			queue_event(smc,EVENT_PCM+np,PC_START) ;
			break ;
		}
		phy->t_val[9] = FALSE ;
		switch (smc->s.sas) {
		case SMT_DAS :
			/*
			 * MAC intended on output
			 */
			if (phy->pc_mode == PM_TREE) {
				if ((np == PB) || ((np == PA) &&
				(smc->y[PB].mib->fddiPORTConnectState !=
					PCM_ACTIVE)))
					phy->t_val[9] = TRUE ;
			}
			else {
				if (np == PB)
					phy->t_val[9] = TRUE ;
			}
			break ;
		case SMT_SAS :
			if (np == PS)
				phy->t_val[9] = TRUE ;
			break ;
#ifdef	CONCENTRATOR
		case SMT_NAC :
			/*
			 * MAC intended on output
			 */
			if (np == PB)
				phy->t_val[9] = TRUE ;
			break ;
#endif
		}
		mib->fddiPORTMacIndicated.T_val = phy->t_val[9] ;
		break ;
	}
	DB_PCMN(1, "SIG snd %x %x:", bit, phy->t_val[bit]);
}