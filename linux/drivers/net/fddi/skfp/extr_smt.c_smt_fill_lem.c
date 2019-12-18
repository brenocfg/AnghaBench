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
struct smt_p_lem {int /*<<< orphan*/  lem_ct; int /*<<< orphan*/  lem_reject_ct; int /*<<< orphan*/  lem_estimate; int /*<<< orphan*/  lem_alarm; int /*<<< orphan*/  lem_cutoff; scalar_t__ lem_pad2; int /*<<< orphan*/  lem_phy_index; scalar_t__ lem_mib_index; } ;
struct s_smc {TYPE_1__* y; } ;
struct fddi_mib_p {int /*<<< orphan*/  fddiPORTLem_Ct; int /*<<< orphan*/  fddiPORTLem_Reject_Ct; int /*<<< orphan*/  fddiPORTLer_Estimate; int /*<<< orphan*/  fddiPORTLer_Alarm; int /*<<< orphan*/  fddiPORTLer_Cutoff; } ;
struct TYPE_2__ {struct fddi_mib_p* mib; } ;

/* Variables and functions */
 scalar_t__ INDEX_PORT ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_lem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_LEM ; 
 int /*<<< orphan*/  phy_index (struct s_smc*,int) ; 

__attribute__((used)) static void smt_fill_lem(struct s_smc *smc, struct smt_p_lem *lem, int phy)
{
	struct fddi_mib_p	*mib ;

	mib = smc->y[phy].mib ;

	SMTSETPARA(lem,SMT_P_LEM) ;
	lem->lem_mib_index = phy+INDEX_PORT ;
	lem->lem_phy_index = phy_index(smc,phy) ;
	lem->lem_pad2 = 0 ;
	lem->lem_cutoff = mib->fddiPORTLer_Cutoff ;
	lem->lem_alarm = mib->fddiPORTLer_Alarm ;
	/* long term bit error rate */
	lem->lem_estimate = mib->fddiPORTLer_Estimate ;
	/* # of rejected connections */
	lem->lem_reject_ct = mib->fddiPORTLem_Reject_Ct ;
	lem->lem_ct = mib->fddiPORTLem_Ct ;	/* total number of errors */
}