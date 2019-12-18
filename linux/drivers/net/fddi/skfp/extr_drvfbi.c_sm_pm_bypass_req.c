#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sas; } ;
struct s_smc {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_DAS ; 
#define  BP_DEINSERT 129 
#define  BP_INSERT 128 
 int /*<<< orphan*/  DAS_BYP_INS ; 
 int /*<<< orphan*/  DAS_BYP_RMV ; 
 int /*<<< orphan*/  DB_ECMN (int,char*,char*) ; 
 scalar_t__ SMT_DAS ; 
 int /*<<< orphan*/  outp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sm_pm_bypass_req(struct s_smc *smc, int mode)
{
	DB_ECMN(1, "ECM : sm_pm_bypass_req(%s)",
		mode == BP_INSERT ? "BP_INSERT" : "BP_DEINSERT");

	if (smc->s.sas != SMT_DAS)
		return ;

#ifdef	PCI
	switch(mode) {
	case BP_INSERT :
		outp(ADDR(B0_DAS),DAS_BYP_INS) ;	/* insert station */
		break ;
	case BP_DEINSERT :
		outp(ADDR(B0_DAS),DAS_BYP_RMV) ;	/* bypass station */
		break ;
	}
#endif
}