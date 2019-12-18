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
struct smt_p_sde {int /*<<< orphan*/  sde_type; int /*<<< orphan*/  sde_mac_count; int /*<<< orphan*/  sde_master; int /*<<< orphan*/  sde_non_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  fddiSMTMaster_Ct; int /*<<< orphan*/  fddiSMTNonMaster_Ct; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMMACS ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_sde*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_SDE ; 
 int /*<<< orphan*/  SMT_SDE_CONCENTRATOR ; 
 int /*<<< orphan*/  SMT_SDE_STATION ; 

__attribute__((used)) static void smt_fill_sde(struct s_smc *smc, struct smt_p_sde *sde)
{
	SMTSETPARA(sde,SMT_P_SDE) ;
	sde->sde_non_master = smc->mib.fddiSMTNonMaster_Ct ;
	sde->sde_master = smc->mib.fddiSMTMaster_Ct ;
	sde->sde_mac_count = NUMMACS ;		/* only 1 MAC */
#ifdef	CONCENTRATOR
	sde->sde_type = SMT_SDE_CONCENTRATOR ;
#else
	sde->sde_type = SMT_SDE_STATION ;
#endif
}