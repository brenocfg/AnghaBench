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
struct TYPE_5__ {scalar_t__ sas; } ;
struct s_smc {TYPE_2__ s; TYPE_1__* y; } ;
struct TYPE_6__ {int /*<<< orphan*/  para; scalar_t__ timer; } ;
struct TYPE_4__ {scalar_t__ pmd_scramble; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLC (int,scalar_t__) ; 
 int /*<<< orphan*/  PLCS_CONTROL_C_S ; 
 int /*<<< orphan*/  PLCS_CONTROL_C_U ; 
 int /*<<< orphan*/  PLCS_FASSERT_S ; 
 int /*<<< orphan*/  PLCS_FASSERT_U ; 
 int /*<<< orphan*/  PLCS_FDEASSERT_S ; 
 int /*<<< orphan*/  PLCS_FDEASSERT_U ; 
 int PLC_REVISION_A ; 
 int PLC_REV_MASK ; 
 int /*<<< orphan*/  PL_CLASS_S ; 
 scalar_t__ PL_CNTRL_A ; 
 scalar_t__ PL_CNTRL_B ; 
 scalar_t__ PL_CNTRL_C ; 
 scalar_t__ PL_INTR_EVENT ; 
 scalar_t__ PL_INTR_MASK ; 
 int /*<<< orphan*/  PL_PCM_STOP ; 
 scalar_t__ PL_STATUS_A ; 
 scalar_t__ PL_T_FOT_ASS ; 
 scalar_t__ PL_T_FOT_DEASS ; 
 int PS ; 
 scalar_t__ SMT_SAS ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plc_clear_irq (struct s_smc*,int) ; 
 int /*<<< orphan*/  plc_imsk_na ; 
 TYPE_3__* pltm ; 

__attribute__((used)) static void plc_init(struct s_smc *smc, int p)
{
	int	i ;
#ifndef	MOT_ELM
	int	rev ;	/* Revision of PLC-x */
#endif	/* MOT_ELM */

	/* transit PCM state machine to MAINT state */
	outpw(PLC(p,PL_CNTRL_B),0) ;
	outpw(PLC(p,PL_CNTRL_B),PL_PCM_STOP) ;
	outpw(PLC(p,PL_CNTRL_A),0) ;

	/*
	 * if PLC-S then set control register C
	 */
#ifndef	MOT_ELM
	rev = inpw(PLC(p,PL_STATUS_A)) & PLC_REV_MASK ;
	if (rev != PLC_REVISION_A)
#endif	/* MOT_ELM */
	{
		if (smc->y[p].pmd_scramble) {
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_S) ;
#ifdef	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_S) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_S) ;
#endif	/* MOT_ELM */
		}
		else {
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_U) ;
#ifdef	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_U) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_U) ;
#endif	/* MOT_ELM */
		}
	}

	/*
	 * set timer register
	 */
	for ( i = 0 ; pltm[i].timer; i++)	/* set timer parameter reg */
		outpw(PLC(p,pltm[i].timer),pltm[i].para) ;

	(void)inpw(PLC(p,PL_INTR_EVENT)) ;	/* clear interrupt event reg */
	plc_clear_irq(smc,p) ;
	outpw(PLC(p,PL_INTR_MASK),plc_imsk_na); /* enable non active irq's */

	/*
	 * if PCM is configured for class s, it will NOT go to the
	 * REMOVE state if offline (page 3-36;)
	 * in the concentrator, all inactive PHYS always must be in
	 * the remove state
	 * there's no real need to use this feature at all ..
	 */
#ifndef	CONCENTRATOR
	if ((smc->s.sas == SMT_SAS) && (p == PS)) {
		outpw(PLC(p,PL_CNTRL_B),PL_CLASS_S) ;
	}
#endif
}