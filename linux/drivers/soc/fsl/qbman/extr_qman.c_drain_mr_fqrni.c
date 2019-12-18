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
union qm_mr_entry {int verb; } ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int QM_MR_VERB_FQRNI ; 
 int QM_MR_VERB_TYPE_MASK ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  qm_mr_cci_consume (struct qm_portal*,int) ; 
 union qm_mr_entry* qm_mr_current (struct qm_portal*) ; 
 int /*<<< orphan*/  qm_mr_next (struct qm_portal*) ; 
 int /*<<< orphan*/  qm_mr_pvb_update (struct qm_portal*) ; 

__attribute__((used)) static int drain_mr_fqrni(struct qm_portal *p)
{
	const union qm_mr_entry *msg;
loop:
	qm_mr_pvb_update(p);
	msg = qm_mr_current(p);
	if (!msg) {
		/*
		 * if MR was full and h/w had other FQRNI entries to produce, we
		 * need to allow it time to produce those entries once the
		 * existing entries are consumed. A worst-case situation
		 * (fully-loaded system) means h/w sequencers may have to do 3-4
		 * other things before servicing the portal's MR pump, each of
		 * which (if slow) may take ~50 qman cycles (which is ~200
		 * processor cycles). So rounding up and then multiplying this
		 * worst-case estimate by a factor of 10, just to be
		 * ultra-paranoid, goes as high as 10,000 cycles. NB, we consume
		 * one entry at a time, so h/w has an opportunity to produce new
		 * entries well before the ring has been fully consumed, so
		 * we're being *really* paranoid here.
		 */
		mdelay(1);
		qm_mr_pvb_update(p);
		msg = qm_mr_current(p);
		if (!msg)
			return 0;
	}
	if ((msg->verb & QM_MR_VERB_TYPE_MASK) != QM_MR_VERB_FQRNI) {
		/* We aren't draining anything but FQRNIs */
		pr_err("Found verb 0x%x in MR\n", msg->verb);
		return -1;
	}
	qm_mr_next(p);
	qm_mr_cci_consume(p, 1);
	goto loop;
}