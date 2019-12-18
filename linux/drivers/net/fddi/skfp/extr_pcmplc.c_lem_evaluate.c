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
typedef  int u_long ;
struct s_smc {int dummy; } ;
struct lem_counter {int lem_errors; int lem_float_ber; int /*<<< orphan*/  lem_on; } ;
struct s_phy {scalar_t__ np; void* pc_lem_fail; struct fddi_mib_p* mib; struct lem_counter lem; } ;
struct fddi_mib_p {int fddiPORTLem_Ct; int fddiPORTLer_Estimate; int fddiPORTLer_Alarm; int fddiPORTLerFlag; int fddiPORTLer_Cutoff; int /*<<< orphan*/  fddiPORTLem_Reject_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_PCMN (int,char*,char,...) ; 
 scalar_t__ EVENT_PCM ; 
 void* FALSE ; 
 scalar_t__ INDEX_PORT ; 
 scalar_t__ PB ; 
 int /*<<< orphan*/  PC_START ; 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_LINK_ERR_CTR ; 
 int /*<<< orphan*/  SMT_COND_PORT_LER ; 
 void* TRUE ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_ler_alarm_check (struct s_smc*,struct s_phy*,int) ; 
 int /*<<< orphan*/  smt_port_off_event (struct s_smc*,scalar_t__) ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void lem_evaluate(struct s_smc *smc, struct s_phy *phy)
{
	int ber ;
	u_long errors ;
	struct lem_counter *lem = &phy->lem ;
	struct fddi_mib_p	*mib ;
	int			cond ;

	mib = phy->mib ;

	if (!lem->lem_on)
		return ;

	errors = inpw(PLC(((int) phy->np),PL_LINK_ERR_CTR)) ;
	lem->lem_errors += errors ;
	mib->fddiPORTLem_Ct += errors ;

	errors = lem->lem_errors ;
	/*
	 * calculation is called on a intervall of 8 seconds
	 *	-> this means, that one error in 8 sec. is one of 8*125*10E6
	 *	the same as BER = 10E-9
	 * Please note:
	 *	-> 9 errors in 8 seconds mean:
	 *	   BER = 9 * 10E-9  and this is
	 *	    < 10E-8, so the limit of 10E-8 is not reached!
	 */

		if (!errors)		ber = 15 ;
	else	if (errors <= 9)	ber = 9 ;
	else	if (errors <= 99)	ber = 8 ;
	else	if (errors <= 999)	ber = 7 ;
	else	if (errors <= 9999)	ber = 6 ;
	else	if (errors <= 99999)	ber = 5 ;
	else	if (errors <= 999999)	ber = 4 ;
	else	if (errors <= 9999999)	ber = 3 ;
	else	if (errors <= 99999999)	ber = 2 ;
	else	if (errors <= 999999999) ber = 1 ;
	else				ber = 0 ;

	/*
	 * weighted average
	 */
	ber *= 100 ;
	lem->lem_float_ber = lem->lem_float_ber * 7 + ber * 3 ;
	lem->lem_float_ber /= 10 ;
	mib->fddiPORTLer_Estimate = lem->lem_float_ber / 100 ;
	if (mib->fddiPORTLer_Estimate < 4) {
		mib->fddiPORTLer_Estimate = 4 ;
	}

	if (lem->lem_errors) {
		DB_PCMN(1, "LEM %c :", phy->np == PB ? 'B' : 'A');
		DB_PCMN(1, "errors      : %ld", lem->lem_errors);
		DB_PCMN(1, "sum_errors  : %ld", mib->fddiPORTLem_Ct);
		DB_PCMN(1, "current BER : 10E-%d", ber / 100);
		DB_PCMN(1, "float BER   : 10E-(%d/100)", lem->lem_float_ber);
		DB_PCMN(1, "avg. BER    : 10E-%d", mib->fddiPORTLer_Estimate);
	}

	lem->lem_errors = 0L ;

#ifndef	SLIM_SMT
	cond = (mib->fddiPORTLer_Estimate <= mib->fddiPORTLer_Alarm) ?
		TRUE : FALSE ;
#ifdef	SMT_EXT_CUTOFF
	smt_ler_alarm_check(smc,phy,cond) ;
#endif	/* nSMT_EXT_CUTOFF */
	if (cond != mib->fddiPORTLerFlag) {
		smt_srf_event(smc,SMT_COND_PORT_LER,
			(int) (INDEX_PORT+ phy->np) ,cond) ;
	}
#endif

	if (	mib->fddiPORTLer_Estimate <= mib->fddiPORTLer_Cutoff) {
		phy->pc_lem_fail = TRUE ;		/* flag */
		mib->fddiPORTLem_Reject_Ct++ ;
		/*
		 * "forgive 10e-2" if we cutoff so we can come
		 * up again ..
		 */
		lem->lem_float_ber += 2*100 ;

		/*PC81b*/
#ifdef	CONCENTRATOR
		DB_PCMN(1, "PCM: LER cutoff on port %d cutoff %d",
			phy->np, mib->fddiPORTLer_Cutoff);
#endif
#ifdef	SMT_EXT_CUTOFF
		smt_port_off_event(smc,phy->np);
#else	/* nSMT_EXT_CUTOFF */
		queue_event(smc,(int)(EVENT_PCM+phy->np),PC_START) ;
#endif	/* nSMT_EXT_CUTOFF */
	}
}