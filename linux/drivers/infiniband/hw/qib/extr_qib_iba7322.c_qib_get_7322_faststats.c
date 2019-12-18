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
typedef  scalar_t__ u64 ;
struct timer_list {int dummy; } ;
struct qib_pportdata {int link_speed_active; int lflags; TYPE_3__* dd; TYPE_1__* cpspec; int /*<<< orphan*/  link_speed_supported; } ;
struct qib_devdata {int num_pports; int flags; int /*<<< orphan*/  stats_timer; scalar_t__ diag_client; struct qib_pportdata* pport; } ;
struct TYPE_6__ {TYPE_2__* cspec; int /*<<< orphan*/  eep_st_lock; scalar_t__ traffic_wds; } ;
struct TYPE_5__ {scalar_t__ r1; } ;
struct TYPE_4__ {scalar_t__ qdr_dfe_on; scalar_t__ qdr_dfe_time; } ;

/* Variables and functions */
 int ACTIVITY_TIMER ; 
 int HZ ; 
 int /*<<< orphan*/  QDR_STATIC_ADAPT_INIT ; 
 int /*<<< orphan*/  QDR_STATIC_ADAPT_INIT_R1 ; 
 int QIBL_LINKACTIVE ; 
 int QIBL_LINKARMED ; 
 int QIBL_LINKINIT ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDRCV ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDSEND ; 
 int QIB_IB_QDR ; 
 int QIB_INITTED ; 
 struct qib_devdata* dd ; 
 int /*<<< orphan*/  force_h1 (struct qib_pportdata*) ; 
 struct qib_devdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  krp_static_adapt_dis (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ qib_portcntr_7322 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stats_timer ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void qib_get_7322_faststats(struct timer_list *t)
{
	struct qib_devdata *dd = from_timer(dd, t, stats_timer);
	struct qib_pportdata *ppd;
	unsigned long flags;
	u64 traffic_wds;
	int pidx;

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;

		/*
		 * If port isn't enabled or not operational ports, or
		 * diags is running (can cause memory diags to fail)
		 * skip this port this time.
		 */
		if (!ppd->link_speed_supported || !(dd->flags & QIB_INITTED)
		    || dd->diag_client)
			continue;

		/*
		 * Maintain an activity timer, based on traffic
		 * exceeding a threshold, so we need to check the word-counts
		 * even if they are 64-bit.
		 */
		traffic_wds = qib_portcntr_7322(ppd, QIBPORTCNTR_WORDRCV) +
			qib_portcntr_7322(ppd, QIBPORTCNTR_WORDSEND);
		spin_lock_irqsave(&ppd->dd->eep_st_lock, flags);
		traffic_wds -= ppd->dd->traffic_wds;
		ppd->dd->traffic_wds += traffic_wds;
		spin_unlock_irqrestore(&ppd->dd->eep_st_lock, flags);
		if (ppd->cpspec->qdr_dfe_on && (ppd->link_speed_active &
						QIB_IB_QDR) &&
		    (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
				    QIBL_LINKACTIVE)) &&
		    ppd->cpspec->qdr_dfe_time &&
		    time_is_before_jiffies(ppd->cpspec->qdr_dfe_time)) {
			ppd->cpspec->qdr_dfe_on = 0;

			qib_write_kreg_port(ppd, krp_static_adapt_dis(2),
					    ppd->dd->cspec->r1 ?
					    QDR_STATIC_ADAPT_INIT_R1 :
					    QDR_STATIC_ADAPT_INIT);
			force_h1(ppd);
		}
	}
	mod_timer(&dd->stats_timer, jiffies + HZ * ACTIVITY_TIMER);
}