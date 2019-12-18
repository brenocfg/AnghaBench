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
struct qib_user_info {int dummy; } ;
struct qib_devdata {unsigned int first_user_ctxt; unsigned int ctxts_extrabuf; int pbufsctxt; unsigned int piobcnt2k; unsigned int unit; int palign; int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,int,unsigned int) ;int /*<<< orphan*/  pport; int /*<<< orphan*/  (* f_sendctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ pio2k_bufbase; } ;
struct qib_ctxtdata {unsigned int ctxt; int piocnt; unsigned int pio_base; int /*<<< orphan*/  wait; int /*<<< orphan*/  flag; scalar_t__ subctxt_cnt; int /*<<< orphan*/  ppd; scalar_t__ rcvhdrtail_kvaddr; scalar_t__ urgent_poll; scalar_t__ urgent; scalar_t__ tidcursor; scalar_t__ piobufs; struct qib_devdata* dd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  QIB_CTXT_MASTER_UNINIT ; 
 int QIB_RCVCTRL_CTXT_ENB ; 
 int QIB_RCVCTRL_TIDFLOW_ENB ; 
 int /*<<< orphan*/  QIB_SENDCTRL_AVAIL_BLIP ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_KERN ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_USER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qib_ctxtdata* ctxt_fp (struct file*) ; 
 int /*<<< orphan*/  qib_chg_pioavailkernel (struct qib_devdata*,int,unsigned int,int /*<<< orphan*/ ,struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  qib_clear_rcvhdrtail (struct qib_ctxtdata*) ; 
 int qib_create_rcvhdrq (struct qib_devdata*,struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,unsigned int,unsigned int) ; 
 int qib_setup_eagerbufs (struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ subctxt_fp (struct file*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qib_do_user_init(struct file *fp,
			    const struct qib_user_info *uinfo)
{
	int ret;
	struct qib_ctxtdata *rcd = ctxt_fp(fp);
	struct qib_devdata *dd;
	unsigned uctxt;

	/* Subctxts don't need to initialize anything since master did it. */
	if (subctxt_fp(fp)) {
		ret = wait_event_interruptible(rcd->wait,
			!test_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag));
		goto bail;
	}

	dd = rcd->dd;

	/* some ctxts may get extra buffers, calculate that here */
	uctxt = rcd->ctxt - dd->first_user_ctxt;
	if (uctxt < dd->ctxts_extrabuf) {
		rcd->piocnt = dd->pbufsctxt + 1;
		rcd->pio_base = rcd->piocnt * uctxt;
	} else {
		rcd->piocnt = dd->pbufsctxt;
		rcd->pio_base = rcd->piocnt * uctxt +
			dd->ctxts_extrabuf;
	}

	/*
	 * All user buffers are 2KB buffers.  If we ever support
	 * giving 4KB buffers to user processes, this will need some
	 * work.  Can't use piobufbase directly, because it has
	 * both 2K and 4K buffer base values.  So check and handle.
	 */
	if ((rcd->pio_base + rcd->piocnt) > dd->piobcnt2k) {
		if (rcd->pio_base >= dd->piobcnt2k) {
			qib_dev_err(dd,
				    "%u:ctxt%u: no 2KB buffers available\n",
				    dd->unit, rcd->ctxt);
			ret = -ENOBUFS;
			goto bail;
		}
		rcd->piocnt = dd->piobcnt2k - rcd->pio_base;
		qib_dev_err(dd, "Ctxt%u: would use 4KB bufs, using %u\n",
			    rcd->ctxt, rcd->piocnt);
	}

	rcd->piobufs = dd->pio2k_bufbase + rcd->pio_base * dd->palign;
	qib_chg_pioavailkernel(dd, rcd->pio_base, rcd->piocnt,
			       TXCHK_CHG_TYPE_USER, rcd);
	/*
	 * try to ensure that processes start up with consistent avail update
	 * for their own range, at least.   If system very quiet, it might
	 * have the in-memory copy out of date at startup for this range of
	 * buffers, when a context gets re-used.  Do after the chg_pioavail
	 * and before the rest of setup, so it's "almost certain" the dma
	 * will have occurred (can't 100% guarantee, but should be many
	 * decimals of 9s, with this ordering), given how much else happens
	 * after this.
	 */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);

	/*
	 * Now allocate the rcvhdr Q and eager TIDs; skip the TID
	 * array for time being.  If rcd->ctxt > chip-supported,
	 * we need to do extra stuff here to handle by handling overflow
	 * through ctxt 0, someday
	 */
	ret = qib_create_rcvhdrq(dd, rcd);
	if (!ret)
		ret = qib_setup_eagerbufs(rcd);
	if (ret)
		goto bail_pio;

	rcd->tidcursor = 0; /* start at beginning after open */

	/* initialize poll variables... */
	rcd->urgent = 0;
	rcd->urgent_poll = 0;

	/*
	 * Now enable the ctxt for receive.
	 * For chips that are set to DMA the tail register to memory
	 * when they change (and when the update bit transitions from
	 * 0 to 1.  So for those chips, we turn it off and then back on.
	 * This will (very briefly) affect any other open ctxts, but the
	 * duration is very short, and therefore isn't an issue.  We
	 * explicitly set the in-memory tail copy to 0 beforehand, so we
	 * don't have to wait to be sure the DMA update has happened
	 * (chip resets head/tail to 0 on transition to enable).
	 */
	if (rcd->rcvhdrtail_kvaddr)
		qib_clear_rcvhdrtail(rcd);

	dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_CTXT_ENB | QIB_RCVCTRL_TIDFLOW_ENB,
		      rcd->ctxt);

	/* Notify any waiting slaves */
	if (rcd->subctxt_cnt) {
		clear_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag);
		wake_up(&rcd->wait);
	}
	return 0;

bail_pio:
	qib_chg_pioavailkernel(dd, rcd->pio_base, rcd->piocnt,
			       TXCHK_CHG_TYPE_KERN, rcd);
bail:
	return ret;
}