#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct qib_pportdata {scalar_t__ link_speed_enabled; int lastibcstat; int /*<<< orphan*/  port; TYPE_3__* dd; TYPE_1__* cpspec; } ;
struct TYPE_7__ {int /*<<< orphan*/  unit; TYPE_2__* cspec; } ;
struct TYPE_6__ {scalar_t__ r1; } ;
struct TYPE_5__ {int qdr_reforce; int qdr_dfe_on; scalar_t__ qdr_dfe_time; int /*<<< orphan*/  chase_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBCStatusA_0 ; 
#define  IB_7322_LT_STATE_CFGENH 131 
 int IB_7322_LT_STATE_CFGIDLE ; 
#define  IB_7322_LT_STATE_CFGRCVFCFG 130 
 int IB_7322_LT_STATE_CFGTEST ; 
 int IB_7322_LT_STATE_CFGWAITENH ; 
#define  IB_7322_LT_STATE_CFGWAITRMT 129 
 int IB_7322_LT_STATE_LINKUP ; 
 int IB_7322_LT_STATE_POLLACTIVE ; 
 int IB_7322_LT_STATE_SLEEPQUIET ; 
#define  IB_7322_LT_STATE_TXREVLANES 128 
 int IB_PHYSPORTSTATE_LINK_ERR_RECOVER ; 
 int IB_PHYSPORTSTATE_RECOVERY_IDLE ; 
 int IB_PHYSPORTSTATE_RECOVERY_RETRAIN ; 
 int IB_PHYSPORTSTATE_RECOVERY_WAITRMT ; 
 scalar_t__ IS_QME (TYPE_3__*) ; 
 scalar_t__ IS_QMH (TYPE_3__*) ; 
 int /*<<< orphan*/  LinkSpeedQDR ; 
 int /*<<< orphan*/  LinkTrainingState ; 
 int /*<<< orphan*/  QDR_STATIC_ADAPT_DOWN ; 
 int /*<<< orphan*/  QDR_STATIC_ADAPT_DOWN_R1 ; 
 int /*<<< orphan*/  QIB_CHASE_TIME ; 
 scalar_t__ QIB_IB_QDR ; 
 scalar_t__ SYM_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adj_tx_serdes (struct qib_pportdata*) ; 
 int /*<<< orphan*/  disable_chase (struct qib_pportdata*,unsigned long,int) ; 
 int /*<<< orphan*/  force_h1 (struct qib_pportdata*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  krp_static_adapt_dis (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qib_7322_phys_portstate (int) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdes_7322_los_enable (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  time_after (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_serdes_issues(struct qib_pportdata *ppd, u64 ibcst)
{
	u8 ibclt;
	unsigned long tnow;

	ibclt = (u8)SYM_FIELD(ibcst, IBCStatusA_0, LinkTrainingState);

	/*
	 * Detect and handle the state chase issue, where we can
	 * get stuck if we are unlucky on timing on both sides of
	 * the link.   If we are, we disable, set a timer, and
	 * then re-enable.
	 */
	switch (ibclt) {
	case IB_7322_LT_STATE_CFGRCVFCFG:
	case IB_7322_LT_STATE_CFGWAITRMT:
	case IB_7322_LT_STATE_TXREVLANES:
	case IB_7322_LT_STATE_CFGENH:
		tnow = jiffies;
		if (ppd->cpspec->chase_end &&
		     time_after(tnow, ppd->cpspec->chase_end))
			disable_chase(ppd, tnow, ibclt);
		else if (!ppd->cpspec->chase_end)
			ppd->cpspec->chase_end = tnow + QIB_CHASE_TIME;
		break;
	default:
		ppd->cpspec->chase_end = 0;
		break;
	}

	if (((ibclt >= IB_7322_LT_STATE_CFGTEST &&
	      ibclt <= IB_7322_LT_STATE_CFGWAITENH) ||
	     ibclt == IB_7322_LT_STATE_LINKUP) &&
	    (ibcst & SYM_MASK(IBCStatusA_0, LinkSpeedQDR))) {
		force_h1(ppd);
		ppd->cpspec->qdr_reforce = 1;
		if (!ppd->dd->cspec->r1)
			serdes_7322_los_enable(ppd, 0);
	} else if (ppd->cpspec->qdr_reforce &&
		(ibcst & SYM_MASK(IBCStatusA_0, LinkSpeedQDR)) &&
		 (ibclt == IB_7322_LT_STATE_CFGENH ||
		ibclt == IB_7322_LT_STATE_CFGIDLE ||
		ibclt == IB_7322_LT_STATE_LINKUP))
		force_h1(ppd);

	if ((IS_QMH(ppd->dd) || IS_QME(ppd->dd)) &&
	    ppd->link_speed_enabled == QIB_IB_QDR &&
	    (ibclt == IB_7322_LT_STATE_CFGTEST ||
	     ibclt == IB_7322_LT_STATE_CFGENH ||
	     (ibclt >= IB_7322_LT_STATE_POLLACTIVE &&
	      ibclt <= IB_7322_LT_STATE_SLEEPQUIET)))
		adj_tx_serdes(ppd);

	if (ibclt != IB_7322_LT_STATE_LINKUP) {
		u8 ltstate = qib_7322_phys_portstate(ibcst);
		u8 pibclt = (u8)SYM_FIELD(ppd->lastibcstat, IBCStatusA_0,
					  LinkTrainingState);
		if (!ppd->dd->cspec->r1 &&
		    pibclt == IB_7322_LT_STATE_LINKUP &&
		    ltstate != IB_PHYSPORTSTATE_LINK_ERR_RECOVER &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_RETRAIN &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_WAITRMT &&
		    ltstate != IB_PHYSPORTSTATE_RECOVERY_IDLE)
			/* If the link went down (but no into recovery,
			 * turn LOS back on */
			serdes_7322_los_enable(ppd, 1);
		if (!ppd->cpspec->qdr_dfe_on &&
		    ibclt <= IB_7322_LT_STATE_SLEEPQUIET) {
			ppd->cpspec->qdr_dfe_on = 1;
			ppd->cpspec->qdr_dfe_time = 0;
			/* On link down, reenable QDR adaptation */
			qib_write_kreg_port(ppd, krp_static_adapt_dis(2),
					    ppd->dd->cspec->r1 ?
					    QDR_STATIC_ADAPT_DOWN_R1 :
					    QDR_STATIC_ADAPT_DOWN);
			pr_info(
				"IB%u:%u re-enabled QDR adaptation ibclt %x\n",
				ppd->dd->unit, ppd->port, ibclt);
		}
	}
}