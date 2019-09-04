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
typedef  int /*<<< orphan*/  u64 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {int flags; int /*<<< orphan*/  (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QIBPORTCNTR_PKTRCV ; 
 int /*<<< orphan*/  QIBPORTCNTR_PKTSEND ; 
 int /*<<< orphan*/  QIBPORTCNTR_SENDSTALL ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDRCV ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDSEND ; 
 int QIB_PRESENT ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

int qib_snapshot_counters(struct qib_pportdata *ppd, u64 *swords,
			  u64 *rwords, u64 *spkts, u64 *rpkts,
			  u64 *xmit_wait)
{
	int ret;
	struct qib_devdata *dd = ppd->dd;

	if (!(dd->flags & QIB_PRESENT)) {
		/* no hardware, freeze, etc. */
		ret = -EINVAL;
		goto bail;
	}
	*swords = dd->f_portcntr(ppd, QIBPORTCNTR_WORDSEND);
	*rwords = dd->f_portcntr(ppd, QIBPORTCNTR_WORDRCV);
	*spkts = dd->f_portcntr(ppd, QIBPORTCNTR_PKTSEND);
	*rpkts = dd->f_portcntr(ppd, QIBPORTCNTR_PKTRCV);
	*xmit_wait = dd->f_portcntr(ppd, QIBPORTCNTR_SENDSTALL);

	ret = 0;

bail:
	return ret;
}