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
typedef  int u8 ;
typedef  int u32 ;
struct qib_pportdata {int lflags; int /*<<< orphan*/  lflags_lock; struct qib_devdata* dd; } ;
struct qib_devdata {int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int IB_LINKCMD_ACTIVE ; 
 int IB_LINKCMD_ARMED ; 
 int IB_LINKCMD_DOWN ; 
 int IB_LINKINITCMD_DISABLE ; 
 int IB_LINKINITCMD_NOP ; 
 int IB_LINKINITCMD_POLL ; 
 int IB_LINKINITCMD_SLEEP ; 
 int QIBL_LINKACTIVE ; 
 int QIBL_LINKARMED ; 
 int QIBL_LINKINIT ; 
 int QIBL_LINKV ; 
 int /*<<< orphan*/  QIB_IB_CFG_LSTATE ; 
#define  QIB_IB_LINKACTIVE 133 
#define  QIB_IB_LINKARM 132 
#define  QIB_IB_LINKDOWN 131 
#define  QIB_IB_LINKDOWN_DISABLE 130 
#define  QIB_IB_LINKDOWN_ONLY 129 
#define  QIB_IB_LINKDOWN_SLEEP 128 
 int qib_wait_linkstate (struct qib_pportdata*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 

int qib_set_linkstate(struct qib_pportdata *ppd, u8 newstate)
{
	u32 lstate;
	int ret;
	struct qib_devdata *dd = ppd->dd;
	unsigned long flags;

	switch (newstate) {
	case QIB_IB_LINKDOWN_ONLY:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_NOP);
		/* don't wait */
		ret = 0;
		goto bail;

	case QIB_IB_LINKDOWN:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_POLL);
		/* don't wait */
		ret = 0;
		goto bail;

	case QIB_IB_LINKDOWN_SLEEP:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_SLEEP);
		/* don't wait */
		ret = 0;
		goto bail;

	case QIB_IB_LINKDOWN_DISABLE:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_DISABLE);
		/* don't wait */
		ret = 0;
		goto bail;

	case QIB_IB_LINKARM:
		if (ppd->lflags & QIBL_LINKARMED) {
			ret = 0;
			goto bail;
		}
		if (!(ppd->lflags & (QIBL_LINKINIT | QIBL_LINKACTIVE))) {
			ret = -EINVAL;
			goto bail;
		}
		/*
		 * Since the port can be ACTIVE when we ask for ARMED,
		 * clear QIBL_LINKV so we can wait for a transition.
		 * If the link isn't ARMED, then something else happened
		 * and there is no point waiting for ARMED.
		 */
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_LINKV;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_ARMED | IB_LINKINITCMD_NOP);
		lstate = QIBL_LINKV;
		break;

	case QIB_IB_LINKACTIVE:
		if (ppd->lflags & QIBL_LINKACTIVE) {
			ret = 0;
			goto bail;
		}
		if (!(ppd->lflags & QIBL_LINKARMED)) {
			ret = -EINVAL;
			goto bail;
		}
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_ACTIVE | IB_LINKINITCMD_NOP);
		lstate = QIBL_LINKACTIVE;
		break;

	default:
		ret = -EINVAL;
		goto bail;
	}
	ret = qib_wait_linkstate(ppd, lstate, 10);

bail:
	return ret;
}