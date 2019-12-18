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
typedef  int u_short ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int FM_SPCEPDA0 ; 
 int FM_SPCEPDA1 ; 
 int FM_SPCEPDS ; 
 int FM_SQLCKA0 ; 
 int FM_SQLCKS ; 
 int /*<<< orphan*/  FM_ST1L ; 
 int /*<<< orphan*/  FM_ST1U ; 
 int FM_STBURA0 ; 
 int FM_STBURA1 ; 
 int FM_STBURS ; 
 int FM_STECFRMA0 ; 
 int FM_STEFRMA0 ; 
 int FM_STEFRMS ; 
 int FM_STXABRA0 ; 
 int FM_STXABRS ; 
 int FM_SXMTABT ; 
 int /*<<< orphan*/  SMT_E0133 ; 
 int /*<<< orphan*/  SMT_E0133_MSG ; 
 int /*<<< orphan*/  SMT_E0134 ; 
 int /*<<< orphan*/  SMT_E0134_MSG ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  formac_tx_restart (struct s_smc*) ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_restart_tx (struct s_smc*) ; 

void mac1_irq(struct s_smc *smc, u_short stu, u_short stl)
{
	int	restart_tx = 0 ;
again:

	/*
	 * parity error: note encoding error is not possible in tag mode
	 */
	if (stl & (FM_SPCEPDS  |	/* parity err. syn.q.*/
		   FM_SPCEPDA0 |	/* parity err. a.q.0 */
		   FM_SPCEPDA1)) {	/* parity err. a.q.1 */
		SMT_PANIC(smc,SMT_E0134, SMT_E0134_MSG) ;
	}
	/*
	 * buffer underrun: can only occur if a tx threshold is specified
	 */
	if (stl & (FM_STBURS  |		/* tx buffer underrun syn.q.*/
		   FM_STBURA0 |		/* tx buffer underrun a.q.0 */
		   FM_STBURA1)) {	/* tx buffer underrun a.q.2 */
		SMT_PANIC(smc,SMT_E0133, SMT_E0133_MSG) ;
	}

	if ( (stu & (FM_SXMTABT |		/* transmit abort */
		     FM_STXABRS |		/* syn. tx abort */
		     FM_STXABRA0)) ||		/* asyn. tx abort */
	     (stl & (FM_SQLCKS |		/* lock for syn. q. */
		     FM_SQLCKA0)) ) {		/* lock for asyn. q. */
		formac_tx_restart(smc) ;	/* init tx */
		restart_tx = 1 ;
		stu = inpw(FM_A(FM_ST1U)) ;
		stl = inpw(FM_A(FM_ST1L)) ;
		stu &= ~ (FM_STECFRMA0 | FM_STEFRMA0 | FM_STEFRMS) ;
		if (stu || stl)
			goto again ;
	}

	if (stu & (FM_STEFRMA0 |	/* end of asyn tx */
		    FM_STEFRMS)) {	/* end of sync tx */
		restart_tx = 1 ;
	}

	if (restart_tx)
		llc_restart_tx(smc) ;
}